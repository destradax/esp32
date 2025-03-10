#include <Arduino.h>

#include "credentials.h"
#include "webserver.h"
#include "websocket.h"
#include "wifi.h"

bool serverStarted = false;
bool printResult = true;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("");
  Serial.flush();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  if (connectToWifi(ssid, passPhrase)) {
    serverSetup();
    webSocketSetup();

    serverStarted = true;
  }
}

void loop(void) {
  if (serverStarted) {
    serverListen();
    webSocketListen();
  }

  if (printResult) {
    if (serverStarted) {
      Serial.println("Server listening");
    } else {
      Serial.println("Server did not start");
    }

    printResult = false;
  }
}