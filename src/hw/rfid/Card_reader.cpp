#include "Card_reader.h"

Card_reader::Card_reader(SPI* spi) : mfrc522(spi)
{

}

Card_reader::~Card_reader()
{

}

bool Card_reader::Is_card()
{
    uint8_t byte = mfrc522_request(PICC_REQALL, rfid_data);
    if (byte == CARD_FOUND) return true;

    return false;
}

Device_data Card_reader::Get_card_number()
{
    mfrc522_get_card_serial(rfid_data);
    card_data.dev_name = "Card_reader";
    card_data.dev_data.clear();
    for(const auto data : rfid_data)
    {
        card_data.dev_data.push_back((int)data);
    }
    return card_data;
}