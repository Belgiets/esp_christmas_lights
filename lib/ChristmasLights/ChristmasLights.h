#ifndef ChristmasLights_h
#define ChristmasLights_h

#include <Arduino.h>
#include <FirebaseArduino.h>

class ChristmasLights {
private:
  int _pin;
  void run(void);
  void stop(void);

public:
  ChristmasLights(int pin);
  bool status;
  int level;
  int mode;
  void handle(void);
  void parseFBObject(FirebaseObject jbObject);
};

#endif