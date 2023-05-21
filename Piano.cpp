#include "Piano.h"

Piano::Piano() {
	this->servos = nullptr;
    this->startIndex = 0;
}

Piano::Piano(vector<int> pins, vector<int> inv, int startIndex = 0):startIndex(startIndex) {
	servos = new Servo[PIANO_SIZE];
    
    for(auto it = pins.begin(); it != pins.end(); ++it) {
		try {
			this->servos[it - pins.begin()] = Servo(*it);
		} catch (const char* msg) {
			cerr << msg << endl;
		}
	}

    if(gpioInitialise() < 0) return -1; // Init GPIO
   	gpioSetSignalFunc(SIGINT, this->sleep);

    for(auto it = inv.begin(); it != inv.end(); ++it) {
		this->servos[it - inv.begin()].setInv(*it);
		this->servos[it - inv.begin()].noteOff();
		gpioSleep(PI_TIME_RELATIVE, 0, 200000);
	}
}

Piano::~Piano() {
    delete[] servos;
	this->startIndex = 0;
}

void Piano::sleep(int signum) {
	for(int i = 0; i < PIANO_SIZE; i++) {
		this->servos[i].noteSleep();
	}	
}

ostream& operator<< (ostream& os, const Piano& p) {
    os << "=============================" << endl;
	os << "==== SERVO-GPIO  MATCHES ====" << endl;
	for(int i = 0; i < PIANO_SIZE; i++) {
		os << "Note number " << i + p.startIndex << " is at pin " << p.servos[i] << endl;
	}
	os << "=============================" << endl;
    return os;
}

Servo& Piano::operator[] (int index) {
    return this->servos[index - this->startIndex];
}

