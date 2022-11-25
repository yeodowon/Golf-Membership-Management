#include "Piezo.h"

Piezo::Piezo(int pwm) : pwmpin(pwm)
{
    wiringPiSetup();
    softPwmCreate(pwmpin, 0, 100);
}

Piezo::~Piezo()
{

}

void Piezo::Beep(int repeat)
{
	int  i;
	for(i=0; i < repeat; i++)
	{
        softPwmWrite(pwmpin, 50);
        delay(10);
    }
    softPwmWrite(pwmpin, 0);
}    