#include "FBDB.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <ChristmasLights.h>

FBDB::FBDB(String firebaseHost, String actionPath) {
  _firebaseHost = firebaseHost;
  _path = actionPath;
};

void FBDB::begin(void) {
  Firebase.begin(_firebaseHost);
  Serial.println("Firebase started");
};

ChristmasLights FBDB::getValues() {
  ChristmasLights chrLights;
  chrLights.status = Firebase.getBool(_path + "/status");
  chrLights.level = Firebase.getInt(_path + "/level");
  chrLights.mode = Firebase.getInt(_path + "/mode");
  
  if (Firebase.failed()) {
    Serial.println("Getting data failed");
  }

  return chrLights;
};
