#ifndef POUR_H_
#define POUR_H_

#include "Arduino.h"

class Pour {

	public:
		Pour(byte pin, unsigned int pulses, unsigned int et);

    byte getPin();
    unsigned int getPulses();
    unsigned int getEt();

    String toJson();

    float toMl(unsigned int pulsesPerLitre);
    float toL(unsigned int pulsesPerLitre);
    float toOz(unsigned int pulsesPerLitre);

	private:
		byte pin;
    unsigned int pulses;
    unsigned int et;
};

#endif
