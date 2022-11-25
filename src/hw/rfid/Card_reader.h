#ifndef CARD_READER_H
#define CARD_READER_H

#include <iostream>
#include <string>
#include "mfrc522.h"
#include "Device_data.h"

using namespace std;

class Card_reader : public mfrc522
{
private:
    uint8_t rfid_data[16];
    Device_data card_data;

public:
    Card_reader(SPI* spi);
    virtual ~Card_reader();
    bool Is_card();
    Device_data Get_card_number();
};

#endif