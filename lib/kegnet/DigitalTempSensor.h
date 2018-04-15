#ifndef DIGITALTEMPSENSOR_H_
#define DIGITALTEMPSENSOR_H_

#include "Conf.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#include <math.h>

class DigitalTempSensor {

	public:
		DigitalTempSensor(Conf *conf);

    void process(unsigned long currentTs);
		float getLastTempC();
		bool hasTemp();
		unsigned long getLastTempTs();

	private:
		const unsigned int DS_DELAY = 900;         // Reading the temperature from the DS18x20 can take up to 750ms

		Conf *conf;

    OneWire* oneWire;
    DallasTemperature* sensor;
		DeviceAddress sensorAddress;

    bool tmpRequested = false;
		float lastTempC = -999;
		unsigned long lastTempReqestedTs = 0;
		unsigned long lastTempTs = 0;

		void requestTemp(unsigned long currentTs);
		void updateTemp(unsigned long currentTs);

		float readTempC();
};

#endif
