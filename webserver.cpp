
#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "indexHtml.h"

ESP8266WebServer server(80);

void serverSetup() {
  Serial.print("Registering endpoints... ");

  server.on("/", HTTP_GET, []() {
    Serial.println("Serving index file");
    server.send(200, "text/html; charset=utf-8", indexHtml);
  });

  server.on("/turnOn", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/plain; charset=utf-8", "OK");
  });

  server.on("/turnOff", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, HIGH);
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