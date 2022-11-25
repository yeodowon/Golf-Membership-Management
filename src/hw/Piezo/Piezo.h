#ifndef PIEZO_H
#define PIEZO_H

#pragma once

#include <softPwm.h>
#include <wiringPi.h>

class Piezo
{
private:
    int pwmpin;


public:
    Piezo(int pwm);
    ~Piezo();
    void Beep(int repeat);


};

#endif