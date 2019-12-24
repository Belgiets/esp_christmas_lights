#include "FBDB.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

FBDB::FBDB(String firebaseHost) {
  _firebaseHost = firebaseHost;
};

void FBDB::begin(void) {
  Firebase.begin(_firebaseHost);
  Serial.println("Firebase started");
};

FirebaseObject FBDB::getValues() {
  FirebaseObject fbValues = Firebase.get("values");
  
  if (Firebase.failed()) {
    Serial.println("Getting status data failed");
    Serial.println(Firebase.error());  
  }

  return fbValues;
};
