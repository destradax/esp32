
#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "builtinfiles.h"

ESP8266WebServer server(80);

void serverSetup(const char *ssid, const char *passPhrase) {
  Serial.println("Starting WebServer...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passPhrase);
  WiFi.setHostname("webserveros");

  Serial.print("Connect to WiFi: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Registering service handlers...");

  server.on("/", HTTP_GET, []() {
    Serial.println("Serving index file");
    server.send(200, "text/html; charset=utf-8", indexFile);
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

  server.enableCORS(true);

  server.enableETag(true);

  server.begin();
  Serial.print("Hostname:");
  Serial.println(WiFi.getHostname());
}

void serverStart() { server.handleClient(); }