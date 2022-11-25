#ifndef COM_DEV_H
#define COM_DEV_H
#include "Tcp_server.h"
#include <thread>

class Com_dev
{
private:
    Tcp_server* card_tcp_server;

public:
    Com_dev(Tcp_server* server);
    virtual ~Com_dev();
    void Send_data(uint8_t* car_num);

private:

};

#endif