#ifndef SG90_H
#define SG90_H

class Sg90
{
private:
    const bool ON = 1;
    const bool OFF = 0;
    int pin_number;
    bool motor_state;
    void writePin(bool pin_state);

public:
    Sg90(int pin);
    virtual ~Sg90();
    void Door_control(int pin_number);
};

#endif