#include "ChristmasLights.h"
#include <Arduino.h>

ChristmasLights::ChristmasLights(int pin) {
  _pin = pin;
};

void ChristmasLights::test(void) {
  analogWrite(_pin, 1023);
};