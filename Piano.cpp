#include "Piano.h"

Piano::Piano() {
	this->servos = nullptr;
    this->startIndex = 0;
}

Piano::Piano(vector<int> pins, vector<int> inv, int startIndex = 0):startIndex(startIndex) {
	servos = new Servo[PIANO_SIZE];
    
    for(auto it = pins.begin(); it != pins.end(); ++it) {
		try {
			this->servos[it - mappingNoteGPIO.begin()] = Servo(*it);
		} catch (const char* msg) {
			cerr << msg << endl;
		}
	}

    if(gpioInitialise() < 0) return -1; // Init GPIO
   	gpioSetSignalFunc(SIGINT, stop);

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

ostream& operator<< (ostream& os, const Piano& p) {
    os << "=============================" << endl;
	os << "==== SERVO-GPIO  MATCHES ====" << endl;
	for(int i = 0; i < PIANO_SIZE; i++) {
		os << "Note number " << i + p.startIndex << " is at pin " << p[i] << endl;
	}
	os << "=============================" << endl;
    return os;
}

int& Piano::operator[] (int index) {
    return servos[index - this->startIndex];
}

