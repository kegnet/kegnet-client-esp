#ifndef CONF_H_
#define CONF_H_

#include "Bleeper.h"

class Conf: public RootConfiguration {
public:

  Conf();

  persistentIntVar(startupDelayMs, 1500);

  persistentIntVar(buttonPin, 12);
  persistentIntVar(tempPin, 4);
  persistentIntVar(flowPin, 5);

  persistentIntVar(tempPollMs, 1000);
  persistentIntVar(tempExpireMs, 3000);

  persistentIntVar(pulsesPerLitre, 5600);
  persistentIntVar(pourDelayMs, 1500);
  persistentIntVar(minPourPulses, 250);

  persistentIntVar(useF, 1);
  persistentIntVar(useOz, 1);

  void process(unsigned long currentTs);

  String formatFlow(unsigned int pulses);
  String formatTemp(float tempC);

  float toL(unsigned int pulses);
  float toMl(unsigned int pulses);
  float toOz(unsigned int pulses);

  float toF(float tempC);

};

#endif
