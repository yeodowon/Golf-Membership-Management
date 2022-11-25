#ifndef GOLF_MEMBERSHIP_MANAGER_H
#define GOLF_MEMBERSHIP_MANAGER_H

#include <iostream>
#include "Listener.h"
#include "Monitor.h"

class Golf_membership_manager
{
private:
    Listener* listener;

public:
    Golf_membership_manager();
    virtual ~Golf_membership_manager();
    void Run();
};

#endif