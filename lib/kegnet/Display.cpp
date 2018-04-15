#include "Display.h"

Display::Display(Conf *conf, FlowMeter *flowMeter, DigitalTempSensor *tempSensor) {
  this->conf = conf;
  this->flowMeter = flowMeter;
  this->tempSensor = tempSensor;

  tft = new TFT_eSPI();
  tft->init();

  delay(200);

  clear();

  delay(200);

  sprite = new TFT_eSprite(tft);
  sprite->setColorDepth(8);
  sprite->setTextColor(TFT_WHITE, TFT_BLACK);
  sprite->setTextWrap(true, true);
  if (!sprite->loadFont(font)) {
    Serial.println("Failed to load font " + font);
    sprite->setTextFont(1);
    sprite->setTextSize(2);
  }

  // sprite->setColorDepth(8);
  // sprite->createSprite(240, fontSize*2);
  // sprite->loadFont(font);
  // sprite->setTextColor(TFT_WHITE, TFT_BLACK);
  //sprite->setTextWrap(true, true);
}

void Display::process(unsigned long currentTs) {
  if (currentTs - lastRefresh < refreshPeriodMs)
    return;

  if (flowMeter->isPouring()) {
    showPouring(currentTs);
  } else {
    showTemp(currentTs);
  }

  lastRefresh = currentTs;
}

void Display::clear() {
  //tft->fillScreen(TFT_WHITE);
  tft->fillScreen(TFT_BLACK);
}

void Display::showPouring(unsigned long currentTs) {
  writeCenter(conf->formatFlow(flowMeter->getPourProgress()));
}

// void Display::showPour() {
//   String s = String(useOz ? toOz(litres) : toMl(litres), 1);
//   s.concat(useOz ? "oz" : "ml");
//   writeCenter(s, String("Enjoy!"));
//
//   lastMessageTs = millis();
//   lastMessageDelay = pourMessageDelay;
// }
//
// void Display::showNoPour() {
//   writeCenter(String("No Pour"));
//
//   lastMessageTs = millis();
//   lastMessageDelay = noPourMessageDelay;
// }

void Display::showTemp(unsigned long currentTs) {
  if (currentTs - lastMessageTs < lastMessageDelay)
    return;

  if (tempSensor->hasTemp()) {
    writeCenter(conf->formatTemp(tempSensor->getLastTempC()));
  } else {
    writeCenter("...");
  }
}

void Display::showStatus(String s) {
  writeCenter(s);
  lastMessageTs = millis();
  lastMessageDelay = statusDelay;
}

void Display::showStatus(String s1, String s2) {
  writeCenter(s1, s2);
  lastMessageTs = millis();
  lastMessageDelay = statusDelay;
}

void Display::writeCenter(String s) {
  unsigned int w = sprite->textWidth(s);
  unsigned int h = fontSize;

  prepareSprite(w, h);

  sprite->drawString(s, 0, 0);
  sprite->pushSprite(0, 0);
}

void Display::writeCenter(String s1, String s2) {
  unsigned int w = max(sprite->textWidth(s1), sprite->textWidth(s2));
  unsigned int h = fontSize * 2;

  prepareSprite(w, h);

  sprite->drawString(s1, 0, 0);
  sprite->drawString(s2, 0, fontSize);
  sprite->pushSprite(0, 0);
}

void Display::prepareSprite(unsigned int w, unsigned int h) {
  if (w == 0 || h == 0) {
    Serial.println("WARN: 0 size sprite");
    return;
  }

  if (w != lastW || h != lastH) {
    if (lastW > 0) {
      sprite->fillSprite(TFT_BLACK);
      sprite->pushSprite(0, 0);
      sprite->deleteSprite();
    }

    sprite->createSprite(w, h);

    lastW = w;
    lastH = h;
  }

  sprite->fillSprite(TFT_BLACK);
}
