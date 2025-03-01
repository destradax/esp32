// @file WebServer.ino
// @brief Example implementation using the ESP8266 WebServer.
//
// See also README.md for instructions and hints.
//
// Changelog:
// 21.07.2021 creation, first version

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "secrets.h"  // add WLAN Credentials in here.
#include "builtinfiles.h"  // add WLAN Credentials in here.

// name of the server. You reach it using http://webserver
#define HOSTNAME "webserver"

// need a WebServer for http access on port 80.
ESP8266WebServer server(80);

// Setup everything to make the webserver work.
void setup(void) {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Starting WebServer...");

  // start WiFI
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");

  WiFi.begin(ssid, passPhrase);

  // allow to address the device by the given name e.g. http://webserver
  WiFi.setHostname(HOSTNAME);

  Serial.println("Connect to WiFi...");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Register service handlers...\n");

  // register a redirect handler when only domain name is given.
  server.on("/", HTTP_GET, []() {
    // server.send(200, "text/html; charset=utf-8", "<html><head><title>Hola</title></head><body>El body</body></html>");
    // server.send(200, "text/html; charset=utf-8", "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\" /> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /> <title>Document</title> <style> body { text-align: center; } .buttons { display: flex; justify-content: stretch; gap: 24px; } .buttons button { flex: 1; padding: 2em 0; } </style> </head> <body> <h1>Blink</h1> <div class=\"buttons\"> <button id=\"btnTurnOn\">Turn On</button> <button id=\"btnTurnOff\">Turn Off</button> </div> <script> const turnOnButton = document.getElementById('btnTurnOn'); const turnOffButton = document.getElementById('btnTurnOff'); turnOnButton.onclick = () => { fetch('/turnOn'); }; turnOffButton.onclick = () => { fetch('/turnOff'); }; </script> </body> </html>");
    server.send(200, "text/html; charset=utf-8", indexFile);
  });

  // register some REST services
  server.on("/turnOn", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/plain; charset=utf-8", "OK");
  });

  server.on("/turnOff", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/plain; charset=utf-8", "OK");
  });

  // enable CORS header in webserver results
  server.enableCORS(true);

  // enable ETAG header in webserver results from serveStatic handler
  server.enableETag(true);

  server.begin();
  Serial.print("hostname=");
  Serial.println(WiFi.getHostname());
}  // setup


// run the server...
void loop(void) {
  server.handleClient();
}  // loop()

// end.