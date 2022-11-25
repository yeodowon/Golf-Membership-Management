#ifndef MANAGE_BUTTON_H
#define MANAGE_BUTTON_H
#include "Button.h"
#include "Device_data.h"

class Manage_button : public Button
{
private:
    Device_data button_data;
public:
    Manage_button(int pin, std::string name);
    virtual ~Manage_button();
    bool Check_button();
    Device_data Get_button_data();
};

#endif