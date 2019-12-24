#include "ChristmasLights.h"
#include <Arduino.h>
#include <FirebaseArduino.h>

ChristmasLights::ChristmasLights(int pin) {
  _pin = pin;
  status = 0;
  level = 10;
  mode = 1;
};

void ChristmasLights::handle(void) {
  if (status == 1) {
    run(); 
  } else {
    stop();
  }
};

void ChristmasLights::run(void) {
  analogWrite(_pin, 1023);
};

void ChristmasLights::stop(void) {
  analogWrite(_pin, 0);
}

void ChristmasLights::parseFBObject(FirebaseObject jbObject) {
  status = jbObject.getInt("status");
  level = jbObject.getInt("level");
  mode = jbObject.getInt("mode");
}