#include "Controller.h"

Controller::Controller(Members_manage_service* members_manage_service)
{
    monitor = new Monitor();
    this->members_manage_service = members_manage_service;
}

Controller::~Controller()
{
    delete monitor;
}

void Controller::Update_event(Device_data data)
{
    if(data.dev_name == "Card_reader")
    {
        uint8_t card_number[5];
        for(int i = 0; i < 5; i++)
        {
            card_number[i] = data.dev_data[i];
        }
        members_manage_service->Check_card_num(card_number);
    }

    if(data.dev_name == "Mode_button")
    {
        members_manage_service->Updata_state_event(data.dev_name);
    }

    if(data.dev_name == "Update_button")
    {
        members_manage_service->Updata_state_event(data.dev_name);
    }
    if(data.dev_name == "Exit_button")
    {
        members_manage_service->Updata_state_event(data.dev_name);
    }
    if(data.dev_name == "Finder_button")
    {
        members_manage_service->Updata_state_event(data.dev_name);
    }
}