#include "DigitalTempSensor.h"

DigitalTempSensor::DigitalTempSensor(Conf *conf) {
	this->conf = conf;

  pinMode(conf->tempPin, INPUT);

  this->oneWire = new OneWire(conf->tempPin);
  this->sensor = new DallasTemperature(oneWire);

  sensor->begin();
	sensor->setWaitForConversion(false);
	sensor->setResolution(12);
}

float DigitalTempSensor::getLastTempC() {
	//Serial.print("getLastTempC=");
	//Serial.println(lastTempC);
	return lastTempC;
}

bool DigitalTempSensor::hasTemp() {
	return (lastTempC >= -55 && lastTempC <=  125 && millis() - lastTempTs < conf->tempExpireMs);
}

unsigned long DigitalTempSensor::getLastTempTs() {
	return lastTempTs;
}

void DigitalTempSensor::process(unsigned long currentTs) {
  if (currentTs - lastTempReqestedTs > conf->tempPollMs && !tmpRequested) {
    requestTemp(currentTs);
	}
  if (currentTs - lastTempReqestedTs > DS_DELAY && tmpRequested) {
    updateTemp(currentTs);
		tmpRequested = false;
  }
}

void DigitalTempSensor::requestTemp(unsigned long currentTs) {
	//Serial.println("requestTemp");
  sensor->requestTemperaturesByIndex(0);
	tmpRequested = true;
	lastTempReqestedTs = currentTs;
}

void DigitalTempSensor::updateTemp(unsigned long currentTs) {
  float newTempC = readTempC();
	//Serial.print("newTempC=");
	//Serial.println(newTempC);
  float percentChange = ((newTempC - lastTempC) / newTempC) * 100;
  boolean isValid = true;
  if (newTempC < -55 || newTempC > 125)
    isValid = false;
  if (hasTemp() && abs(percentChange) > 25)
    isValid = false;
  if (isValid) {
    lastTempC = newTempC;
		lastTempTs = currentTs;
		//Serial.println(lastTempC);
  } else {
    Serial.print("WARN: Read bad temp: ");
    Serial.println(newTempC);
  }
}

float DigitalTempSensor::readTempC() {
  return sensor->getTempCByIndex(0);
}
