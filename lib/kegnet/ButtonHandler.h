#ifndef BUTTONHANDLER_H_
#define BUTTONHANDLER_H_

#include "Display.h"
#include "Button.h"

class ButtonHandler {
public:

  ButtonHandler(Conf *conf, Display *display);

  void process(unsigned long currentTs);

private:
  Conf *conf;
  Display *display;
  Button *button;

  unsigned int pushCount = 0;

  int states[4][2] = {{0,0},{0,1},{1,0},{1,1}};
};

#endif
