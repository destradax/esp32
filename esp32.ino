#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "credentials.h"
#include "webserver.h"
#include "wifi.h"

bool serverStarted = false;
bool printError = true;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  if (connectToWifi(ssid, passPhrase)) {
    serverSetup();
    serverStarted = true;
  }
}

void loop(void) {
  if (serverStarted) {
    serverListen();
  } else if (printError) {
    printError = false;
    Serial.println("Server did not start");
  }
}