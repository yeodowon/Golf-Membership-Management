#include "Members_manage_service.h"
#include <iostream>
#include <wiringPi.h>
#include <stdlib.h>

using namespace std;

Members_manage_service::Members_manage_service()
{
    members_entity = new Members_entity();
    views = new Views();
    sg90 = new Sg90(21);
    members_manager_state = CARD_READER;
    find_mode_state = NAME_SEARCH_MODE;
}

Members_manage_service::Members_manage_service(Com_dev* com_dev)
{
    members_entity = new Members_entity();
    views = new Views();
    sg90 = new Sg90(21);
    this->com_dev = com_dev;
    members_manager_state = CARD_READER;
    find_mode_state = NAME_SEARCH_MODE;
}

Members_manage_service::~Members_manage_service()
{
    delete views;
    delete sg90;
}

void Members_manage_service::Updata_state_event(std::string dev_name)
{
    if(dev_name == "Update_button") members_entity->Memory_to_DB();

    if(dev_name == "Exit_button") Exit_program();

    if(dev_name == "Finder_button") Search_member();

    switch(members_manager_state)
    {
        case CARD_READER:
            if(dev_name == "Mode_button" || dev_name == "REGISTER_MODE")
            {
                printf("REGISTER\n");
                members_manager_state = CARD_REGISTER;
                views->Monitor_view("REGISTER_MODE");
                views->Lcd_view("REGISTER_MODE");
                views->Led_view("REGISTER_MODE");
            }
            break;
        case CARD_REGISTER:
            if(dev_name == "Mode_button" || dev_name == "DELETE_MODE")
            {
                members_manager_state = CARD_DELETE;
                views->Monitor_view("DELETE_MODE");
                views->Lcd_view("DELETE_MODE");
                views->Led_view("DELETE_MODE");
            }
            break;
        case CARD_DELETE:
            if(dev_name == "Mode_button" || dev_name == "CHANGE_MODE")
            {
                members_manager_state = CARD_CHANGE;
                views->Monitor_view("CHANGE_MODE");
                views->Lcd_view("CHANGE_MODE");
                views->Led_view("CHANGE_MODE");
            }
            break;
        case CARD_CHANGE:
            if(dev_name == "Mode_button" || dev_name == "READER_MODE")
            {
                members_manager_state = CARD_READER;
                views->Monitor_view("READER_MODE");
                views->Lcd_view("READER_MODE");
                views->Led_view("READER_MODE");
            }
            break;
    }
}

void Members_manage_service::Check_card_num(uint8_t* card_num)
{
    switch(members_manager_state)
    {

        case CARD_READER:
            if(members_entity->Find_member_info(card_num))
            {
                members_entity->Print_member_info(card_num);
                printf("Registered Member!\n\n");                
                com_dev->Send_data(card_num);
                sg90->Door_control(21);
            }
            else 
            {
                printf("Not Registered Member!\n\n");

                printf("REGISTER this card?(y/n) : ");
                cin >> select;
                if(select == 'y')
                { 
                    Updata_state_event("REGISTER_MODE");
                } 
                else 
                {
                    system("clear");
                    members_manager_state = CARD_CHANGE;
                    Updata_state_event("READER_MODE");
                    break;
                }
            }

            break;

        case CARD_REGISTER:
            if(members_entity->Find_member_info(card_num))
            {
                printf("\n<Check Member>\n");
                members_entity->Print_member_info(card_num);
                printf("\nRegistered Member!\n");
                printf("Change the information?(y/n) : ");
                cin >> select;
                if(select == 'y')
                {
                    members_manager_state = CARD_DELETE;
                    Updata_state_event("CHANGE_MODE");
                    break;
                }
                if(select == 'n')
                {
                    system("clear");
                    members_manager_state = CARD_CHANGE;
                    Updata_state_event("READER_MODE");
                    break;
                }
            }
            else Card_register(card_num);
            break;

        case CARD_DELETE:
            if(members_entity->Find_member_info(card_num))
            {
                members_entity->Print_member_info(card_num);
                printf("\n Really Delete?(Y/N) : ");
                cin >> select;
                if(select == 'y')
                {
                    members_entity->Del_member_info(card_num);
                    printf("Delete Complete!!\n");
                }
                if(select == 'n')
                {
                    system("clear");
                    members_manager_state = CARD_REGISTER;
                    Updata_state_event("DELETE_MODE");
                    break;
                }
            }
            else printf("Not Registered Member!\n Retry detect card.\n");
            break;

        case CARD_CHANGE:
            if(members_entity->Find_member_info(card_num))
            {
                members_entity->Print_member_info(card_num);
                printf("\nChange member information\n\n");
                printf("Really change the information?(y/n) : ");
                cin >> select;
                if(select == 'y')
                {
                    if(members_entity->Change_member_info(card_num))
                    {
                        members_manager_state = CARD_DELETE;
                        Updata_state_event("CHANGE_MODE");
                    }
                }
                else 
                {
                    members_manager_state = CARD_DELETE;
                    Updata_state_event("CHANGE_MODE");
                    break;
                }
            }
            else 
            {
                printf("Not Registered Member!\nREGISTER this card?(y/n) : \n");
                cin >> select;
                if(select == 'y')
                {
                    system("clear");
                    members_manager_state = CARD_READER;
                    Updata_state_event("REGISTER_MODE");
                }
                else
                {
                    system("clear");
                    members_manager_state = CARD_DELETE;
                    Updata_state_event("CHANGE_MODE");
                }
            }
            break;
    }
}

void Members_manage_service::Set_com_dev(Com_dev* com_dev)
{
    this->com_dev = com_dev;
}

void Members_manage_service::Card_register(uint8_t* card_num)
{
    Members_info temp_member;

    temp_member.id = members_entity->vecMembers_list.size();
        
    char name[20], address[40], phone_number[15];
    cout << "name : ";
    cin >> name;

    cout << "address : ";
    cin >> address;

    cout << "phone_number : ";
    cin >> phone_number;

    strcpy(temp_member.name, name);
    strcpy(temp_member.address, address);
    strcpy(temp_member.phone_number, phone_number);
    memcpy(temp_member.card_num, card_num, sizeof(temp_member.card_num));
    
    members_entity->Add_member_info(temp_member);

    printf("\nMember REGISTERed!\n");
    members_entity->Print_member_info(card_num);
    printf("\nPress 'y' Continue REGISTER... \n");

    cin >> select;
    if(select == 'y')
    {
        members_manager_state = CARD_READER;
        Updata_state_event("REGISTER_MODE");
    }
}

void Members_manage_service::Search_member()
{
    string keyword;

    system("clear");
    cout << "<SEARCH MODE>" << endl;
    views->Lcd_view("SEARCH_MODE");

    switch(find_mode_state)
    {
    case NAME_SEARCH_MODE:
        printf("Search member(name / exit->READER_MODE, mode->CHANGE SEARCH_MODE) : ");
        cin >> keyword;
        if(members_entity->Find_member_info_by_name(keyword)) 
        {
            cout << "Modified information?(y/n) : ";
            cin >> select;
            if(select == 'y') members_entity->Change_member_info(members_entity->Find_member_card_num_by_name(keyword));
            else cout << "Press button or Detect card...\n";
        }
        else cout << "Not found!\n" << "Press button or Detect card...\n";
        if(keyword == "exit")
        {
            system("clear");
            views->Monitor_view("READER_MODE");
            views->Lcd_view("READER_MODE");
        }
        if(keyword == "mode")
        {
            find_mode_state = ADDRESS_SEARCH_MODE;
            Updata_state_event("Finder_button");
        }
    break;
    case ADDRESS_SEARCH_MODE:
        printf("Search member(address / exit->READER_MODE, mode->CHANGE SEARCH_MODE) : ");
        cin >> keyword;
        if(members_entity->Find_member_info_by_address(keyword)) 
        {
            cout << "Modified information?(y/n) : ";
            cin >> select;
            if(select == 'y') members_entity->Change_member_info(members_entity->Find_member_card_num_by_address(keyword));
            else cout << "Press button or Detect card...\n";
        }
        if(keyword == "exit")
        {
            system("clear");
            views->Monitor_view("READER_MODE");
            views->Lcd_view("READER_MODE");
        }
        if(keyword == "mode")
        {
            find_mode_state = PHONE_NUMBER_SEARCH_MODE;
            Updata_state_event("Finder_button");
        }
    break;
    case PHONE_NUMBER_SEARCH_MODE:
        printf("Search member(phone_number(000-0000-0000) / exit->READER_MODE, mode->CHANGE SEARCH_MODE) : ");
        cin >> keyword;
        if(members_entity->Find_member_info_by_phone_num(keyword)) 
        {
            cout << "Modified information?(y/n) : ";
            cin >> select;
            if(select == 'y') members_entity->Change_member_info(members_entity->Find_member_card_num_by_phone_number(keyword));
            else cout << "Press button or Detect card...\n";
        }
        if(keyword == "exit") 
        {
            system("clear");
            views->Monitor_view("READER_MODE");
            views->Lcd_view("READER_MODE");
        }
        if(keyword == "mode") 
        {
            find_mode_state = NAME_SEARCH_MODE;
            Updata_state_event("Finder_button");
        }
    break;
    }
}

void Members_manage_service::Exit_program()
{
        printf("\nExit Program...\n");
        views->Lcd_view("EXIT");
        delay(2000);
        views->Monitor_view("EXIT");
        views->Led_view("EXIT");
        views->Lcd_view("OFF");        
        exit(0);
}