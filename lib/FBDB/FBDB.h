#ifndef FBDB_h
#define FBDB_h

#include <Arduino.h>
#include <FirebaseArduino.h>

class FBDB {
private:
  String _firebaseHost;

public:
  FBDB(String firebaseHost);
  void begin(void);
  FirebaseObject getValues();
};

#endif
