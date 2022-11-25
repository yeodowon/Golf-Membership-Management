#include "Com_dev.h"

Com_dev::Com_dev(Tcp_server* server)
{
    card_tcp_server = server;
}

Com_dev::~Com_dev()
{
    delete card_tcp_server;
}

void Com_dev::Send_data(uint8_t* car_num)
{
    char Send_buff[1000];
    sprintf(Send_buff, "%02x-%02x-%02x-%02x-%02x", 
    car_num[0], car_num[1], car_num[2], car_num[3], car_num[4]);
    card_tcp_server->sendData(Send_buff, strlen(Send_buff));
}