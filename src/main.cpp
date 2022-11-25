#include <iostream>
#include <thread>
#include <cstring>
#include <string>
#include <wiringPi.h>

#include "mfrc522.h"
#include "Listener.h"
#include "Controller.h"
#include "Members_manage_service.h"
#include "Com_dev.h"
#include "Tcp_server.h"
#include "Golf_membership_manager.h"
#include "Members_entity.h"
#include "Sg90.h"

void Server_thread(Tcp_server *server)
{
    Members_manage_service *members_manage_service = new Members_manage_service();
    Sg90 *sg90 = new Sg90(21);

    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);

            if(strcmp((const char*)recvBuff, "READER_MODE\n") == 0) 
            {
                members_manage_service->members_manager_state = CARD_CHANGE;
                members_manage_service->Updata_state_event("Mode_button");
            }
            if(strcmp((const char*)recvBuff, "RESISTER_MODE\n") == 0) 
            {
                members_manage_service->members_manager_state = CARD_READER;
                members_manage_service->Updata_state_event("Mode_button");     
            }
            if(strcmp((const char*)recvBuff, "DELETE_MODE\n") == 0) 
            {
                members_manage_service->members_manager_state = CARD_REGISTER;
                members_manage_service->Updata_state_event("Mode_button");
            }
            if(strcmp((const char*)recvBuff, "CHANGE_MODE\n") == 0) 
            {
                members_manage_service->members_manager_state = CARD_DELETE;
                members_manage_service->Updata_state_event("Mode_button");
            }
            if(strcmp((const char*)recvBuff, "EXIT\n") == 0) 
            {
                members_manage_service->Updata_state_event("Exit_button");
            }   
            if(strcmp((const char*)recvBuff, "OPEN\n") == 0) 
            {
                sg90->Door_control(21);
            }
            if(strcmp((const char*)recvBuff, "y\n") == 0) 
            {
                members_manage_service->select = 'y';
            }
            if(strcmp((const char*)recvBuff, "n\n") == 0) 
            {
                members_manage_service->select = 'n';
            }
            if(strcmp((const char*)recvBuff, "find\n") == 0) 
            {
                members_manage_service->Search_member();
            }
        } 
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main()
{   
    Tcp_server* card_tcp_server = new Tcp_server(5100);
    Com_dev* com_dev = new Com_dev(card_tcp_server);
    Members_manage_service* members_manage_service = new Members_manage_service(com_dev);
    Controller* controller = new Controller(members_manage_service);
    Listener* listener = new Listener(controller);
    std::thread threadFunc(Server_thread, card_tcp_server);
    
    while(1)
    {
        listener->Check_event();
        delay(50);
    }
    return 0;
}