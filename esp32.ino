#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>

#include "credentials.h"
#include "webserver.h"
#include "wifi.h"

bool serverStarted = false;
bool printResult = true;

const char* webSocketHost = "localhost";
const int webSocketPort = 3001;
const char* webSocketPath = "/";

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("Connected to WebSocket server!");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from WebSocker server");
      break;
    case WStype_TEXT:
      Serial.printf("Received message: %s\n", payload);
      break;
  }
}

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

    webSocket.begin(webSocketHost, webSocketPort, webSocketPath);
    webSocket.onEvent(webSocketEvent);
    serverStarted = true;
  }
}

void loop(void) {
  if (serverStarted) {
    serverListen();
    webSocket.loop();
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