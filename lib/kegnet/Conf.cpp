#include "Conf.h"

Conf::Conf() {
  Bleeper
    .verbose()
    .configuration
      .set(this)
      //.addObserver(new MyObserver(), {&C.wifi.network.port})
      .done()
    // .configurationInterface
    //   .addDefaultWebServer()
    //   .done()
    // .connection
    //   .setSingleConnectionFromPriorityList({
    //       new Wifi(&C.wifi.ssid, &C.wifi.password),
    //       new AP()
    //   })
    //   .done()
    // .storage
    //   //.setDefault() // EEPROM
    //   .set(new SPIFFSStorage(false, false)) // SPIFFS
    //   .done()
    .init();
}

void Conf::process(unsigned long currentTs) {
  Bleeper.handle();
}

String Conf::formatFlow(unsigned int pulses) {
  String s = String(this->useOz ? toOz(pulses) : toMl(pulses), 1);
  s.concat(this->useOz ? "oz" : "ml");
  return s;
}

String Conf::formatTemp(float tempC) {
  String s = String(this->useF ? toF(tempC) : tempC, 1);
  s.concat(this->useF ? "F" : "C"); // TODO: add a degrees symbol (ascii 248)
  return s;
}

float Conf::toL(unsigned int pulses) {
  return ((float)pulses) / ((float)this->pulsesPerLitre);
}

float Conf::toMl(unsigned int pulses) {
  return toL(pulses) * 1000.0;
}

float Conf::toOz(unsigned int pulses) {
  return toL(pulses) * 33.814;
}

float Conf::toF(float tempC) {
  return (tempC * 1.8) + 32.0;
}
