#ifndef VIEWS_H
#define VIEWS_H

#include <iostream>
#include <string>
#include "I2C.h"
#include "LCD.h"
#include "Monitor.h"
#include "Led.h"

class Views
{
private:
    LCD* lcd;
    I2C* i2c;
    Led* led_1;
    Led* led_2;
    Led* led_3;
    Led* led_4;
    Monitor* monitor;

public:
    Views();
    virtual ~Views();
    void Monitor_view(std::string str);
    void Lcd_view(std::string str);
    void Led_view(std::string str);
};

#endif