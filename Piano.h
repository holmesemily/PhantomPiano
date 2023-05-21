#ifndef PIANO_H
#define PIANO_H

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

    public:
        Piano();
        Piano(vector<int> pins, vector<int> inv, int startIndex);
        ~Piano();
        friend ostream& operator<< (ostream& os, const Piano& s);
        int& operator[] (int index);
};

#endif
