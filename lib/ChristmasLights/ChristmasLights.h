#ifndef ChristmasLights_h
#define ChristmasLights_h

#include <Arduino.h>

class ChristmasLights {
private:
  int _pin;

public:
  ChristmasLights(int pin);
  bool status;
  int level;
  int mode;
};

#endif