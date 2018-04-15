#include "Pour.h"

Pour::Pour(byte pin, unsigned int pulses, unsigned int et) {
	this->pin = pin;
	this->pulses = pulses;
	this->et = et;
}

byte Pour::getPin() {
	return pin;
}

unsigned int Pour::getPulses() {
	return pulses;
}

unsigned int Pour::getEt() {
	return et;
}

float Pour::toMl(unsigned int pulsesPerLitre) {

}

float Pour::toL(unsigned int pulsesPerLitre) {

}

float Pour::toOz(unsigned int pulsesPerLitre) {

}

String Pour::toJson() {
	String msg = String();
	msg.concat("{\"pin\":");
	msg.concat(pin);
	msg.concat(",\"pulses\":");
	msg.concat(pulses);
	msg.concat(",\"ms\":");
	msg.concat(et);
	msg.concat("}");
	return msg;
}
