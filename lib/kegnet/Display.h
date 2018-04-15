#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Conf.h"
#include "FlowMeter.h"
#include "DigitalTempSensor.h"

#include "TFT_eSPI.h"

class Display {

	public:
		Display(Conf *conf, FlowMeter *flowMeter, DigitalTempSensor *tempSensor);

		// void showPour();
		// void showNoPour();
		void showStatus(String s);
    void showStatus(String s1, String s2);
    void clear();

		void process(unsigned long currentTs);

	private:
		Conf *conf;
		FlowMeter *flowMeter;
		DigitalTempSensor *tempSensor;

		TFT_eSPI *tft;
		TFT_eSprite *sprite;

		String font = "roboto30";
		byte fontSize = 30;

		unsigned long lastRefresh = 0;
		unsigned int refreshPeriodMs = 100;

		unsigned int pourMessageDelay = 6000;
		unsigned int noPourMessageDelay = 1000;
		unsigned int statusDelay = 2000;

		unsigned long lastMessageTs = 0;
		unsigned int lastMessageDelay = 0;
		unsigned long tempDelay = 1000;

		bool useF = true;
		bool useOz = true;

		unsigned int lastW = 0;
		unsigned int lastH = 0;

		void showPouring(unsigned long currentTs);
		void showTemp(unsigned long currentTs);

		void writeCenter(String s);
		void writeCenter(String s1, String s2);

		void prepareSprite(unsigned int w, unsigned int h);
};

#endif
