#include "wifi.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

#define DELAY_MS 500
#define MAX_RETRIES 20

bool connectToWifi(const char *ssid, const char *passPhrase) {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passPhrase);
  WiFi.setHostname("webserver");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries++ <= MAX_RETRIES) {
    delay(DELAY_MS);
  }

  if (retries >= MAX_RETRIES) {
    Serial.println("Could not connect");
    return false;
  }

  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  return true;
}