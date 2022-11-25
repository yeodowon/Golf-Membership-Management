#include "Members_entity.h"
#include <cstring>  //string.h

using namespace std;

Members_entity::Members_entity()
{
    Load_members_info();
}

Members_entity::~Members_entity()
{

}

void Members_entity::Load_members_info()
{
    fpDB_data = fopen("memberLists.bin", "r");
    if(fpDB_data == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }
    while(fread(&members_info, sizeof(members_info), 1, fpDB_data))
    {
        vecMembers_list.push_back(members_info);
    }
    fclose(fpDB_data);
}

void Members_entity::Add_member_info(Members_info member)
{
    vecMembers_list.push_back(member);
}

void Members_entity::Print_member_info(int index)
{
    if((char)index > vecMembers_list.size()) 
    {
        fprintf(stderr, "out of range member count!\n");
        return;
    }
    printf("=================================================================\n");
    printf("Member Information : ");
    printf("%05d %s %s %s %0x-%0x-%0x-%0x-%0x \n", 
    vecMembers_list[index].id,
    vecMembers_list[index].name,
    vecMembers_list[index].address,
    vecMembers_list[index].phone_number,
    vecMembers_list[index].card_num[0],
    vecMembers_list[index].card_num[1],
    vecMembers_list[index].card_num[2],
    vecMembers_list[index].card_num[3],
    vecMembers_list[index].card_num[4]
    );
    printf("=================================================================\n");
}

void Members_entity::Print_member_info(std::string name)
{
    for (const auto &member : vecMembers_list)
    {
        if (strcmp(member.name, name.c_str()) == 0) 
        {
            Print_member_info(member.id);
            return;
        }
    }
}

void Members_entity::Print_member_info(uint8_t* card_num)
{
    for (const auto &member : vecMembers_list)
        {
            if (memcmp(member.card_num, card_num, sizeof(member.card_num)) == 0) 
            {
                Print_member_info(member.id);
                return;
            }
        }
}

bool Members_entity::Find_member_info_by_name(std::string name)
{
    for (const auto &member : vecMembers_list)
    {
        if (strcmp(member.name, name.c_str()) == 0) 
        {
            printf("Find member!\n");
            Print_member_info(member.id);
            return true;
        }
    }
    return false;
}

bool Members_entity::Find_member_info_by_address(std::string address)
{
    for (const auto &member : vecMembers_list)
    {
        if (strcmp(member.address, address.c_str()) == 0) 
        {
            printf("Find member!\n");
            Print_member_info(member.id);
            return true;
        }
    }
    return false;
}

bool Members_entity::Find_member_info_by_phone_num(std::string phone_number)
{
    for (const auto &member : vecMembers_list)
    {
        if (strcmp(member.phone_number, phone_number.c_str()) == 0) 
        {
            printf("Find member!\n");
            Print_member_info(member.id);
            return true;
        }
    }
    return false;
}

bool Members_entity::Find_member_info(uint8_t* card_num)
{
    for (const auto &member : vecMembers_list)
        {
            if (memcmp(member.card_num, card_num, sizeof(member.card_num)) == 0) return true;
        }
        return false;    
}
int Members_entity::Find_member_id(uint8_t* card_num)
{
    for (const auto &member : vecMembers_list)
    {
        if (memcmp(member.card_num, card_num, sizeof(member.card_num)) == 0) return member.id;
    }
    return 0;
}

uint8_t* Members_entity::Find_member_card_num_by_name(std::string name)
{
    for (auto &member : vecMembers_list)
        {
            if (strcmp(member.name, name.c_str()) == 0) 
            {
                return member.card_num;
            }
        }
}

uint8_t* Members_entity::Find_member_card_num_by_address(std::string address)
{
    for (auto &member : vecMembers_list)
        {
            if (strcmp(member.address, address.c_str()) == 0) 
            {
                return member.card_num;
            }
        }
}

uint8_t* Members_entity::Find_member_card_num_by_phone_number(std::string phone_number)
{
    for (auto &member : vecMembers_list)
        {
            if (strcmp(member.phone_number, phone_number.c_str()) == 0) 
            {
                return member.card_num;
            }
        }
}

bool Members_entity::Del_member_info(uint8_t* card_num)
{
    std::vector<Members_info>::iterator itr_member;

    for(itr_member = vecMembers_list.begin(); itr_member != vecMembers_list.end(); itr_member++)
    {
        if(memcmp(itr_member->card_num, card_num, sizeof(itr_member->card_num)) == 0)
        {
            vecMembers_list.erase(itr_member);
            return true;
        }   
    }
    return false;
}

bool Members_entity::Change_member_info(uint8_t* card_num)
{
    std::vector<Members_info>::iterator itr_member;
    Members_info temp_member;

    temp_member.id = Find_member_id(card_num);

    for(itr_member = vecMembers_list.begin(); itr_member != vecMembers_list.end(); itr_member++)
    {
        if(memcmp(itr_member->card_num, card_num, sizeof(itr_member->card_num)) == 0)
        {
            vecMembers_list.erase(itr_member);
            cout << "Name : " ;
            cin >> temp_member.name;
            cout << "Address : " ;
            cin >> temp_member.address;
            cout << "Phone_number : " ;
            cin >> temp_member.phone_number;
            
            memcpy(temp_member.card_num, card_num, sizeof(temp_member.card_num));
            vecMembers_list.insert(itr_member, temp_member);

            printf("Complete information update!\n");
            return true;
        }   
    }
    return false;
}

void Members_entity::Memory_to_DB()
{
    fpDB_data = fopen("memberLists.bin", "w");
    FILE* fpDB_data2 = fopen("memberLists.txt", "w");

    if(fpDB_data == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }

    for(const auto &member : vecMembers_list)
    {
        fwrite(&member, sizeof(member), 1, fpDB_data);
        fprintf(fpDB_data2, "%05d %s %s %s %0x-%0x-%0x-%0x-%0x\n", member.id, member.name, member.address, 
                member.phone_number, member.card_num[0], member.card_num[1], member.card_num[2], member.card_num[3], 
                member.card_num[4]);
    }
    fclose(fpDB_data);
    fclose(fpDB_data2);
    printf("Update complete!\n");
}

