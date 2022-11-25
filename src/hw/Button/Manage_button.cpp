#include "Manage_button.h"

Manage_button::Manage_button(int pin, std::string name)
: Button(pin)
{
    button_data.dev_name = name;
}

Manage_button::~Manage_button()
{

}
bool Manage_button::Check_button()
{
    if (getState() == RELEASE_ACTIVE) return true;
    return false;
}

Device_data Manage_button::Get_button_data()
{
    button_data.dev_data.clear();
    button_data.dev_data.push_back(1);
    
    return button_data;
}