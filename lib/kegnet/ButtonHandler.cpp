#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(Conf *conf, Display *display) {
  this->conf = conf;
  this->display = display;

  button = new Button(conf->buttonPin, false, false, 20);
}

void ButtonHandler::process(unsigned long currentTs) {
  button->read();
  if (button->wasReleased()) {
    unsigned int state = pushCount % 4;
    conf->useF = states[state][0];
    conf->useOz = states[state][1];
    display->showStatus(conf->useF? "Fahrenheit" : "Celsius", conf->useOz ? "Ounces" : "Milliliters");
    pushCount++;
  }
}
