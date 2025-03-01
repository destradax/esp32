#include <Arduino.h>

#include "credentials.h"
#include "webserver.h"

void setup(void) {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  serverSetup(ssid, passPhrase);
}

void loop(void) { serverStart(); }