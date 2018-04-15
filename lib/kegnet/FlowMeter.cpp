#include "FlowMeter.h"

FlowMeter::FlowMeter(Conf *conf) {
  this->conf = conf;

  pinMode(conf->flowPin, INPUT);

	// this cool magic from https://community.particle.io/t/solved-how-to-register-a-c-instance-method-with-spark-function/13999/24
	auto interruptHandler = std::bind(&FlowMeter::pulse, this);
	attachInterrupt(conf->flowPin, interruptHandler, RISING);
}

void FlowMeter::pulse() {
    interruptCount++;
}

bool FlowMeter::isPouring() {
	return startTs > 0;
}

unsigned int FlowMeter::getPourProgress() {
	return pulseCount;
}

unsigned int FlowMeter::getLastPour() {
	return lastPour;
}

unsigned long FlowMeter::getLastPourTs() {
	return lastPourTs;
}

void FlowMeter::process(unsigned long currentTs) {
	if (interruptCount == 0)
		return;

	if (startTs == 0) {
		startTs = currentTs;
		//Serial.println("start pour");
	}

	if (interruptCount > pulseCount) {
		lastPulseTs = currentTs;
		pulseCount = interruptCount;
		//Serial.println(pulseCount);
		//display->showPouring(isOz ? toOz(pulseCount) : toL(pulseCount), isOz);
	} else if (currentTs - lastPulseTs > conf->pourDelayMs) {
		interruptCount = 0;
		unsigned int et = (currentTs - startTs);
		if (pulseCount < conf->minPourPulses) {
			//display->showNoPour();
			Serial.println("no pour");
		} else {
			lastPourTs = currentTs;
			lastPour = pulseCount;
			//display->showPour(isOz ? toOz(pulseCount) : toL(pulseCount), isOz);
		 	publishPour(pulseCount, et);
		}
		pulseCount = 0;
		startTs = 0;
		lastPulseTs = 0;
	}
}

void FlowMeter::publishPour(unsigned int pulseCount, unsigned int et) {
	String msg = String();
	msg.concat("{\"pin\":");
	msg.concat(conf->flowPin);
	msg.concat(",\"pulses\":");
	msg.concat(pulseCount);
	msg.concat(",\"ms\":");
	msg.concat(et);
	msg.concat("}");

  Serial.println(msg);

	//Particle.publish("pour", msg);
}
