#include "ChristmasLights.h"
#include <Arduino.h>
#include <FirebaseArduino.h>

ChristmasLights::ChristmasLights(int pin) {
  _pin = pin;
  status = 0;
  level = 10;
  mode = 1;
  clearStatuses();
};

void ChristmasLights::clearStatuses() {
  isStatusUpdated = false;
  isLevelUpdated = false;
  isModeUpdated = false;
}

bool ChristmasLights::isUpdated() {
  if (prevStatus != status) {
    isStatusUpdated = true;
    return true;
  }

  if (prevLevel != level) {
    isLevelUpdated = true;
    return true;
  }

  if (prevMode != mode) {
    isModeUpdated = true;
    return true;
  }

  return false;
}

void ChristmasLights::run(void) {
  analogWrite(_pin, 1023);
};

void ChristmasLights::stop(void) {
  analogWrite(_pin, 0);
}

void ChristmasLights::parseFBObject(FirebaseObject jbObject) {
  clearStatuses();
  prevStatus = status;
  status = jbObject.getInt("status");
  prevLevel = level;
  level = jbObject.getInt("level");
  prevMode = mode;
  mode = jbObject.getInt("mode");
}