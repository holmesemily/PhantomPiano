#include "Servo.h"

Servo::Servo() {
	this->Pin_GPIO = 0;
	this->inv = 0;
}

Servo::Servo(int GPIO) {
	if (GPIO < 0 || GPIO > 31) {
		throw "Invalid GPIO. Valid GPIO pins are numbered 0 to 31.";
	}
	this->Pin_GPIO = GPIO;
}

void Servo::setInv(int inv) {
	this->inv = inv;
}

Servo::~Servo() {
	this->Pin_GPIO = 0;
}

int Servo::getGPIO() {
	return this->Pin_GPIO;
}

int Servo::getInv() {
	return this->inv;
}

void Servo::On() {
	if (this->inv == 0) {
		gpioServo(this->Pin_GPIO, 1000);
	} else {
		gpioServo(this->Pin_GPIO, 500);
		//gpioServo(this->Pin_GPIO, 0);
	}
}

void Servo::Off() {
	if (this->inv == 0) {
		gpioServo(this->Pin_GPIO, 500);
		//gpioServo(this->Pin_GPIO, 0);
	} else {
		gpioServo(this->Pin_GPIO, 1000);
	}
}

void Servo::Sleep() {
	gpioServo(this->Pin_GPIO, 0);	
}

ostream& operator<< (ostream& os, const Servo& s) {
        os << s.Pin_GPIO;
        return os;
    }