static const char indexHtml[] PROGMEM =
R"==(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>MVF</title>
    <script type="module" crossorigin>(function(){const r=document.createElement("link").relList;if(r&&r.supports&&r.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))c(e);new MutationObserver(e=>{for(const t of e)if(t.type==="childList")for(const o of t.addedNodes)o.tagName==="LINK"&&o.rel==="modulepreload"&&c(o)}).observe(document,{childList:!0,subtree:!0});function s(e){const t={};return e.integrity&&(t.integrity=e.integrity),e.referrerPolicy&&(t.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?t.credentials="include":e.crossOrigin==="anonymous"?t.credentials="omit":t.credentials="same-origin",t}function c(e){if(e.ep)return;e.ep=!0;const t=s(e);fetch(e.href,t)}})();const i=document.getElementById("pinInput"),u=document.getElementById("btnTurnOn"),f=document.getElementById("btnTurnOff");u.onclick=()=>{const n=i.value;fetch(`/turnOn?pin=${n}`)};f.onclick=()=>{const n=i.value;fetch(`/turnOff?pin=${n}`)};</script>
    <style rel="stylesheet" crossorigin>body{text-align:center}fieldset{display:flex;flex-direction:column;gap:24px;max-width:400px}.labeledInput{align-items:center;display:flex;gap:12px}.labeledInput input{flex:1}button{color:#fff;flex:1;padding:1em 0}#btnTurnOn{background-color:green}#btnTurnOff{background-color:red}</style>
  </head>
  <body>
    <div id="app">
      <h1>MVF</h1>
      <fieldset>
        <legend>Pin Controller</legend>

        <label class="labeledInput">
          Pin:
          <input
            id="pinInput"
            type="number"
            inputmode="numeric"
            placeholder="Leave empty for built-in LED"
          />
        </label>

        <button id="btnTurnOn">Turn ON</button>
        <button id="btnTurnOff">Turn OFF</button>
      </fieldset>
    </div>
  </body>
</html>
)==";