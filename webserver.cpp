
#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "indexHtml.h"

ESP8266WebServer server(80);

void serverSetup() {
  Serial.print("Registering endpoints... ");

  server.on("/", HTTP_GET, []() {
    // keep for indentation
    server.send(200, "text/html; charset=utf-8", indexHtml);
  });

  server.on("/turnOn", HTTP_GET, []() {
    String pinArg = server.arg("pin");

    if (pinArg == NULL) {
      Serial.println("Turning on built-in LED");
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      uint8_t pin = (uint8_t)pinArg.toInt();
      Serial.print("Turning on pin #");
      Serial.println(pin);
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
    }

    server.send(200, "text/plain; charset=utf-8", "OK");
  });

  server.on("/turnOff", HTTP_GET, []() {
    String pinArg = server.arg("pin");

    if (pinArg == NULL) {
      Serial.println("Turning off built-in LED");
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      uint8_t pin = (uint8_t)pinArg.toInt();
      Serial.print("Turning off pin #");
      Serial.println(pin);
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    server.send(200, "text/plain; charset=utf-8", "OK");
  });

  Serial.println("Done");

  Serial.print("Starting WebServer... ");

  server.enableCORS(true);
  server.enableETag(true);
  server.begin();

  Serial.println("Done");
}

void serverListen() { server.handleClient(); }