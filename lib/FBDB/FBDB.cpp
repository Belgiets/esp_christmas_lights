#include "FBDB.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ChristmasLights.h>

FBDB::FBDB(String firebaseHost, String actionPath, int pinLed) {
  _firebaseHost = firebaseHost;
  _path = actionPath;
  _pinLed = pinLed;
};

void FBDB::begin(void) {
  Firebase.begin(_firebaseHost);
  Serial.println("Firebase started");
};

ChristmasLights FBDB::getValues() {
  ChristmasLights chrLights(_pinLed);

  Firebase.setBool("lamp", true);
  // chrLights.status = Firebase.getInt(_path + "/status");
  if (Firebase.failed()) {
    Serial.println("Getting status data failed");
    Serial.println(Firebase.error());  
  }

  // chrLights.level = Firebase.getInt(_path + "/level");
  // if (Firebase.failed()) {
  //   Serial.println("Getting level data failed");
  // }
  
  // chrLights.mode = Firebase.getInt(_path + "/mode");
  // if (Firebase.failed()) {
  //   Serial.println("Getting mode data failed");
  // }
  
  return chrLights;
};
