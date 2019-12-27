#include <Arduino.h>
#include <Storage.h>
#include <CFWiFi.h>
#include <FBDB.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ChristmasLights.h>
#include <WSHtml.h>
#include <RBD_Timer.h>

ESP8266WebServer server(80);
IPAddress ipAP(10, 0, 1, 1);
IPAddress ipGateway(10, 0, 1, 1);
IPAddress subnetMask(255, 255, 255, 0);
Storage storage;
CFWiFi wf(ipAP, ipGateway, subnetMask);
FBDB firebaseDB("christmas-ligths.firebaseio.com");
WSHtml html;
int pinLed = 2;
ChristmasLights chrLights(pinLed);
RBD::Timer firebaseTimer(1000);
// RBD::Timer modeSwitchDelay(1000);
// RBD::Timer ledDelay(50);
// int ledDelayUpIterator = 0;
// int ledDelayDownIterator = 1023;
// int modeSwitchDirection = 0;
// int step = 1;

void createWebServer() {
  server.on("/", []() {
    String form = html.formWifiCreds();
    String body = html.body(form, "Cat feeder: WiFi settings");

    Serial.println("Show settings form");

    server.send(200, "text/html", body);
  });

  server.on("/setting", []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    String body =
        html.body("Settings saved. Reset...", "Cat feeder: WiFi settings");

    Serial.println("Saving wifi client settings");

    if (ssid.length() > 0) {
      Serial.println("Saving ssid");
      storage.setSsid(ssid);
    }

    if (pass.length() > 0) {
      Serial.println("Saving pass");
      storage.setPass(pass);
    }

    if (ssid.length() > 0) {
      // wf.stopAP();
      // Serial.println("AP has been stopped");
      // wf.connectToAP(ssid, pass);
      server.send(200, "text/html", body);
      ESP.restart();
    }
  });

  server.begin();
}

void setup() {
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);
  storage.run();
  delay(2000);

  String ssid = storage.getSsid();
  String pass = storage.getPass();

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

  firebaseTimer.restart();
  // modeSwitchDelay.restart();
  // ledDelay.restart();
}

void loop() {
  server.handleClient();

  // get data from firebase
  if (firebaseTimer.isExpired()) {
    Serial.println("firebaseTimer.isExpired");
    if (wf.connectionStatus == true) {
      FirebaseObject fbValues = firebaseDB.getValues();
      chrLights.parseFBObject(fbValues);
    }

    firebaseTimer.restart();
  }

  // if (chrLights.status == 1 && chrLights.mode == 2) {    
  //   if (modeSwitchDelay.isExpired()) {
  //     modeSwitchDirection = (modeSwitchDirection == 0) ? 1 : 0;
  //     ledDelayUpIterator = 0;
  //     ledDelayDownIterator = 1023;
  //   }

  //   if (ledDelay.isExpired()) {
  //     //go up or down
  //     if (modeSwitchDirection == 0) {
  //       analogWrite(pinLed, ledDelayUpIterator);
  //       ledDelayUpIterator += step;

  //       if (ledDelayDownIterator >= 1024) {
  //         modeSwitchDirection = 1;
  //       }
  //     } else {
  //       analogWrite(pinLed, ledDelayDownIterator);
  //       ledDelayUpIterator -= step;

  //       if (ledDelayDownIterator <= 0) {
  //         modeSwitchDirection = 0;
  //       }
  //     }

  //     ledDelay.restart();
  //   }

  //   modeSwitchDelay.restart();
  // }

  if (chrLights.isUpdated()) {
    Serial.println("chrLights.isUpdated");
    if (chrLights.isStatusUpdated == true) {
      Serial.println("chrLights.isStatusUpdated");
      if (chrLights.status == 1 && chrLights.mode == 1) {
        //TODO: enable
        analogWrite(pinLed, 1023);
      } else {
        //TODO: disable
        analogWrite(pinLed, 0);
      }
    }
  }
}