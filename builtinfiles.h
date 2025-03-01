/**
 * @file builtinfiles.h
 * @brief This file is part of the WebServer example for the ESP8266WebServer.
 *  
 * This file contains long, multiline text variables for  all builtin resources.
 */

// used for $upload.htm
static const char indexFile[] PROGMEM =
R"==(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      body {
        text-align: center;
      }
      .buttons {
        display: flex;
        justify-content: stretch;
        gap: 24px;
      }
      .buttons button {
        flex: 1;
        padding: 2em 0;
      }
    </style>
  </head>
  <body>
    <h1>Blink</h1>
    <div class="buttons">
      <button id="btnTurnOn">Turn ON</button>
      <button id="btnTurnOff">Turn OFF</button>
    </div>

    <script>
      const turnOnButton = document.getElementById('btnTurnOn');
      const turnOffButton = document.getElementById('btnTurnOff');
      turnOnButton.onclick = () => {
        fetch('/turnOn');
      };
      turnOffButton.onclick = () => {
        fetch('/turnOff');
      };
    </script>
  </body>
</html>
)==";