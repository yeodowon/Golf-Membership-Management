#include "Sg90.h"
#include <wiringPi.h>
#include <softPwm.h>

Sg90::Sg90(int pin)
    : pin_number(pin), motor_state(OFF)
{
    wiringPiSetup();
    pinMode(pin_number, OUTPUT);
}

Sg90::~Sg90()
{

}

void Sg90::Door_control(int pin_number)
{
    softPwmCreate(pin_number, 1, 10);
    softPwmWrite(pin_number, 7);
    delay(3000);
    softPwmWrite(pin_number, 2);
    delay(2000);
    softPwmStop(pin_number);
}