#include <FS.h>

#include "Files.h"
#include "Conf.h"
#include "Display.h"
#include "FlowMeter.h"
#include "DigitalTempSensor.h"
#include "ButtonHandler.h"

// #include <ESP8266WiFi.h>
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h>

Conf *conf;
ButtonHandler *buttonHandler;
Display *display;
FlowMeter *flowMeter;
DigitalTempSensor *tempSensor;
// WiFiManager *wifiManager;

void setup()   {
  Serial.begin(115200);

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialization failed!");
  } else {
    listFiles();
  }

  delay(200);

  conf = new Conf();
  tempSensor = new DigitalTempSensor(conf);
  flowMeter = new FlowMeter(conf);
  display = new Display(conf, flowMeter, tempSensor);
  buttonHandler = new ButtonHandler(conf, display);

  //display->showStatus("Connecting", "to wifi");

  // wifiManager = new WiFiManager();
  // wifiManager->setAPCallback(configModeCallback);
  // wifiManager->autoConnect("KEGNET", "kegnet123");
}

// void configModeCallback(WiFiManager *myWiFiManager) {
//   display->showStatus("Wifi setup", "needed");
// }
//

void loop() {
  unsigned long currentTs = millis();

  buttonHandler->process(currentTs);
  conf->process(currentTs);
  flowMeter->process(currentTs);
  tempSensor->process(currentTs);
  display->process(currentTs);

 //
 // if(digitalRead(WIFI_RESET_PIN) == HIGH)
 //   resetRequested = true;
 //
 //  if (resetRequested) {
 //    Serial.println("Wifi reset requested");
 //    display->showStatus("Reset -");
 //    wifiManager->resetSettings();
 //    display->showStatus("Reset /");
 //    resetRequested = false;
 //    delay(1000);
 //    display->showStatus("Reset |");
 //    ESP.restart();
 //    display->showStatus("Reset \\");
 //    delay(1000);
 //    display->showStatus("Reset -");
 //  }
}
