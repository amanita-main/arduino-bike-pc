#include "Screens.h"
#ifndef __ARDUINO_H_INCLUDED__
#define __ARDUINO_INCLUDED__
#include <Arduino.h>
#endif

int IScreen::processKeys() {
  //TODO: read buttons & may be touch, if it is on
  int result = 0;
  if (Serial.available() > 0) {
    // read the incoming byte:
    result = Serial.read();
  }
  return result;
};
int SleepModeScreen::loop() {
  //TODO: update time, draw current total distance, current dist if riding
  //if any button pressed return 1 as signal to awake
  int result = 0;
  int keyPressed = processKeys();
  if (keyPressed > 0) {
    result = 1;
  }
  return result;
};
int MainScreen::loop() {
  //TODO
  Serial.println("loop MainScreen");
  return 0;
};
int SettingsScreen::loop() {
  //TODO
  Serial.println("loop SettingsScreen");
  return 0;
};
int NavigationScreen::loop() {
  //TODO
  Serial.println("loop NavigationScreen");
  return 0;
};
int RouteScreen::loop() {
  //TODO
  Serial.println("loop RouteScreen");
  return 0;
};
