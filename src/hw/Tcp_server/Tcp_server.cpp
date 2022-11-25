#include "Tcp_server.h"

Tcp_server::Tcp_server(int port)
{
    portNum = port;
    clientState = false;
    createSocket();
}

Tcp_server::~Tcp_server()
{
    close(serverSock_fd);
}

int Tcp_server::getServerSocket()
{
    return serverSock_fd;
}

int Tcp_server::getClientSocket()
{
    return clientSock_fd;
}

void Tcp_server::createSocket()
{
    if((serverSock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()\n");
        return;
    }
    int option = 1;
    setsockopt(serverSock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // all local ip
    serv_addr.sin_port = htons(portNum);

    /* bind 함수를 사용하여 서버 소켓의 주소 설정 */
    if(bind(serverSock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind()\n");
        return;
    }

    if(listen(serverSock_fd, 8) < 0) {
        perror("listen()\n");
        return;
    }    
}

int Tcp_server::waitAccept()
{
    char mesg[BUFSIZ];
    /* 클라이언트가 접속하면 접속을 허용하고 클라이언트 소켓 생성 */
    clnt_addr_size = sizeof(client_addr);
    clientSock_fd = accept(serverSock_fd, (struct sockaddr *)&client_addr, &clnt_addr_size);
    if (clientSock_fd < 0)
    {
        perror("accept() error\n");
        return -1;
    }

    /* 네크워크 주소를 문자열로 변경 */
    inet_ntop(AF_INET, &client_addr.sin_addr, mesg, BUFSIZ);
    printf("Client is connected : %s\n", mesg);

    return clientSock_fd;
}

int Tcp_server::recvData(char *recvBuff, size_t size)
{
    int len = read(clientSock_fd, recvBuff, size);
    return len;
}

int Tcp_server::sendData(char *sendBuff, size_t size)
{
    if (!getClientState()) return -1;

    int len = write(clientSock_fd,sendBuff, size);
    return len;
}

void Tcp_server::closeSocket(int socket)
{
    close(socket);
}

bool Tcp_server::getClientState()
{
    return clientState;
}

void Tcp_server::setClientState(bool state)
{
    clientState = state;
}

// void Tcp_server::Socket_control(char *recvBuff)
// {
//     if(strcmp((const char *)recvBuff, "READER_MODE\n") == 0) 
//     {
//         members_manage_service->Updata_state_event("READER_MODE");
//     }
//     if(strcmp((const char *)recvBuff, "RESISTER_MODE\n") == 0) 
//     {
//         members_manage_service->Updata_state_event("RESISTER_MODE");     
//     }
//     if(strcmp((const char *)recvBuff, "DELETE_MODE\n") == 0) 
//     {
//         members_manage_service->Updata_state_event("DELETE_MODE");
//     }
//     if(strcmp((const char *)recvBuff, "CHANGE_MODE\n") == 0) 
//     {
//         members_manage_service->Updata_state_event("CHANGE_MODE");
//     }
//     if(strcmp((const char *)recvBuff, "EXIT\n") == 0) 
//     {
//         members_manage_service->Updata_state_event("EXIT");
//     }    
// }