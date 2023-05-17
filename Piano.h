#ifndef PIANO_H
#define PIANO_H

#include <signal.h>
#include <iostream>
#include <pigpio.h>
#include <vector>

#include "Servo.h"

using namespace std;

#define PIANO_SIZE 24

class Piano {
    private:
        Servo* servos;
        int startIndex;
        static Piano* instancePtr;
    public:
        Piano();
        Piano(vector<int> pins, vector<int> inv, int startIndex);
        ~Piano();
        void sleep(int signum);
        friend ostream& operator<< (ostream& os, const Piano& s);
        Servo& operator[] (int index);
};

#endif
