#ifndef MEMBERS_ENTITY_H
#define MEMBERS_ENTITY_H

#include<iostream>
#include <vector>
#include "Members_info.h"

class Members_entity
{
private:
    Members_info members_info;
    FILE* fpDB_data;

public:
    std::vector<Members_info> vecMembers_list;
    Members_entity();
    virtual ~Members_entity();
    void Load_members_info();
    void Add_member_info(Members_info member);
    bool Del_member_info(uint8_t* card_num);
    bool Change_member_info(uint8_t* card_num);
    bool Change_member_info(std::string* name);
    void Print_member_info(int index);
    void Print_member_info(std::string name);
    void Print_member_info(uint8_t* card_num);
    bool Find_member_info_by_name(std::string name);
    bool Find_member_info_by_address(std::string address);
    bool Find_member_info_by_phone_num(std::string phone_number);
    bool Find_member_info(uint8_t* card_num);
    int Find_member_id(uint8_t* card_num);
    uint8_t* Find_member_card_num_by_name(std::string name);
    uint8_t* Find_member_card_num_by_address(std::string address);
    uint8_t* Find_member_card_num_by_phone_number(std::string phone_number);
    void Memory_to_DB();
};

#endif