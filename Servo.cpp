#include "Servo.h"

Servo::Servo() {
	this->pinGPIO = 0;
	this->inv = 0;
}

Servo::Servo(int GPIO) {
	if (GPIO < 0 || GPIO > 31) {
		throw "Invalid GPIO. Valid GPIO pins are numbered 0 to 31.";
	}
	this->pinGPIO = GPIO;
}

Servo::~Servo() {
	this->pinGPIO = 0;
}

void Servo::setInv(int inv) {
	this->inv = inv;
}

int Servo::getGPIO() {
	return this->pinGPIO;
}

int Servo::getInv() {
	return this->inv;
}

void Servo::noteOn() {
	if (this->inv == 0) {
		gpioServo(this->pinGPIO, 1000);
	} else {
		gpioServo(this->pinGPIO, 500);
	}
    gpioSleep(PI_TIME_RELATIVE, 0, 10);
}

void Servo::noteOff() {
	if (this->inv == 0) {
		gpioServo(this->pinGPIO, 500);
	} else {
		gpioServo(this->pinGPIO, 1000);
	}
    gpioSleep(PI_TIME_RELATIVE, 0, 10);
}

void Servo::noteSleep() {
	gpioServo(this->pinGPIO, 0);	
}

ostream& operator<< (ostream& os, const Servo& s) {
    os << s.pinGPIO;
    return os;
}
