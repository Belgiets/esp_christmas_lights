#ifndef ChristmasLights_h
#define ChristmasLights_h

#include <Arduino.h>
#include <FirebaseArduino.h>

class ChristmasLights {
private:
  int _pin;
  bool prevStatus;
  int prevLevel;
  int prevMode;
  bool isStatusUpdated;
  bool isLevelUpdated;
  bool isModeUpdated;
  void run(void);
  void stop(void);
  void clearStatuses();

public:
  ChristmasLights(int pin);
  bool status;
  int level;
  int mode;
  bool isUpdated();
  void handle(void);
  void parseFBObject(FirebaseObject jbObject);
};

#endif