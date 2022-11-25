#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include "Monitor.h"
#include "Device_data.h"
#include "Members_manage_service.h"

using namespace std;

class Controller
{    
private:
    Monitor* monitor;
    Members_manage_service* members_manage_service;

public:
    Controller(Members_manage_service* members_manage_service);
    virtual ~Controller();
    void Update_event(Device_data data);
};

#endif