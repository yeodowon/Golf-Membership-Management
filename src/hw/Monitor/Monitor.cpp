#include "Monitor.h"
#include <iostream>

using namespace std;

Monitor::Monitor()
{

}

Monitor::~Monitor()
{

}

void Monitor::Print(uint8_t* data, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(data[i] == 0) break;
        printf("%02x ", data[i]);
    }
    cout << endl;
}