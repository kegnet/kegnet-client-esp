#ifndef FLOWMETER_H_
#define FLOWMETER_H_

#include "Arduino.h"
#include "FunctionalInterrupt.h"
#include "Conf.h"

class FlowMeter {

	public:
		FlowMeter(Conf *conf);

    void process(unsigned long currentTs);
		void pulse();

		bool isPouring();
		unsigned int getPourProgress();
		unsigned int getPourComplete();
		unsigned int getLastPour();
		unsigned long getLastPourTs();

	private:
		Conf *conf;

		volatile unsigned int interruptCount = 0;

		unsigned long startTs = 0;
		unsigned int pulseCount = 0;
		unsigned long lastPourTs = 0;
		unsigned long lastPulseTs = 0;

		unsigned int lastPour = 0;

		void publishPour(unsigned int pulses, unsigned int et);
};

#endif
