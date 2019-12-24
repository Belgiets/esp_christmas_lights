#include <Arduino.h>
#include <Storage.h>
#include <CFWiFi.h>
#include <FBDB.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ChristmasLights.h>

int pinLed = 2;
IPAddress ipAP(10, 0, 1, 1);
IPAddress ipGateway(10, 0, 1, 1);
IPAddress subnetMask(255, 255, 255, 0);
Storage storage;
CFWiFi wf(ipAP, ipGateway, subnetMask);
FBDB firebaseDB("christmas-ligths.firebaseio.com");

void setup() {
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);
  storage.run();
  delay(2000);

  String ssid = storage.getSsid();
  String pass = storage.getPass();

  Serial.println("ssid " + ssid);
  Serial.println("pass " + pass);

  if (ssid.length() > 0) {
    if (wf.connectToAP(ssid, pass)) {
      Serial.println("WiFi connected");

      Serial.println("Firebase has been configured");
      firebaseDB.begin();
    } else {
      storage.clear();
      wf.runAP();
      Serial.println("Storage was cleared, AP started");
    }
  } else {
    wf.runAP();
    Serial.println("AP started");
  }
}

void loop() {
  if (wf.connectionStatus == true) {
    // ChristmasLights chrLights = firebaseDB.getValues();

    // Serial.println("chrLights.status - " + chrLights.status);
    // if (chrLights.status == true) {
    //   chrLights.test();
    // }
  }
  
  delay(1000);
}