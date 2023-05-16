#ifndef SERVO_H
#define SERVO_H

#include <iostream>
#include <pigpio.h>

using namespace std;

class Servo {
    private:
        int Pin_GPIO;
        int inv;

    public:
        Servo();
        Servo(int GPIO);
        ~Servo();
        void setInv(int inv);
        int getInv();
        int getGPIO();
        void On();
        void Off();
        void Sleep();
        friend ostream& operator<< (ostream& os, const Servo& s);
};

#endif