#include <WiFi.h>
#include <WebServer.h>

// ===== WIFI =====
const char* ssid = "Robo1";
const char* password = "123456789";

// ===== SERVIDOR =====
WebServer server(80);

// ===== SEGURIDAD: PARADA AUTOMATICA =====
volatile unsigned long ultimaOrdenMovimiento = 0;
const unsigned long TIEMPO_MAXIMO_SIN_ORDEN = 700; // ms

// ===== MOTORES L298N =====
const int IN1 = 16;
const int IN2 = 17;
const int IN3 = 18;
const int IN4 = 19;

// ===== LED =====
const int LED_AZUL = 2;

// ===== PAGINA WEB =====
const char html_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
<meta name="theme-color" content="#071321">
<title>CAR SOCCER | Control ESP32</title>
<style>
:root{--cyan:#54baff;--blue:#1678d3;--ice:#c4e7ff;--red:#ff405d;--panel:rgba(8,10,16,.91)}
*{box-sizing:border-box}
html{min-height:100%;background:#030407}
body{margin:0;min-height:100vh;padding:24px 14px 20px;font-family:system-ui,-apple-system,Segoe UI,Arial,sans-serif;color:#edf5ff;text-align:center;overflow-x:hidden;background:linear-gradient(135deg,#030407,#11151d,#05070b,#10131a);background-size:300% 300%;animation:darkPulse 9s ease-in-out infinite;}
@keyframes darkPulse{0%,100%{background-position:0% 50%;filter:brightness(.78)}50%{background-position:100% 50%;filter:brightness(1.12)}}
body:before{content:"";position:fixed;inset:0;pointer-events:none;opacity:.24;background-image:linear-gradient(rgba(84,186,255,.12) 1px,transparent 1px),linear-gradient(90deg,rgba(84,186,255,.12) 1px,transparent 1px);background-size:34px 34px;mask-image:linear-gradient(to bottom,black,transparent 92%);z-index:0}
.cyber-mark{position:fixed;z-index:0;left:50%;top:47%;transform:translate(-50%,-50%);width:min(92vw,620px);height:auto;opacity:.075;pointer-events:none;filter:drop-shadow(0 0 24px #1687dd);animation:markPulse 5s ease-in-out infinite}
@keyframes markPulse{0%,100%{opacity:.045;filter:drop-shadow(0 0 10px #1687dd)}50%{opacity:.13;filter:drop-shadow(0 0 32px #1687dd)}}
header,main,footer{position:relative;z-index:1}
.brand-icon{width:74px;height:74px;margin:0 auto 13px;display:grid;place-items:center;border:1px solid rgba(84,186,255,.55);border-radius:22px;background:linear-gradient(145deg,#182433,#05070b);box-shadow:0 0 25px rgba(22,120,211,.2),inset 0 0 18px rgba(84,186,255,.08);color:var(--ice);font-size:35px;font-weight:900;transform:rotate(-3deg)}
h1{margin:0;font-size:clamp(34px,8vw,52px);line-height:1.08;font-weight:950;letter-spacing:.11em;color:#f4f7fb;text-shadow:0 0 12px rgba(84,186,255,.35),0 3px 0 #05070b}
h1 span{color:var(--cyan);text-shadow:0 0 18px rgba(84,186,255,.6)}
.subtitle{margin:11px 0 0;font-size:10px;font-weight:800;letter-spacing:.24em;color:#8eb9dc}
.chip{display:inline-flex;align-items:center;gap:7px;margin-top:15px;padding:7px 12px;border:1px solid rgba(84,186,255,.32);border-radius:99px;background:rgba(20,70,112,.16);font-size:10px;font-weight:800;letter-spacing:.13em;color:#a8d8ff}
.dot{width:7px;height:7px;border-radius:50%;background:#75c7ff;box-shadow:0 0 9px #75c7ff;animation:dotPulse 1.8s ease-in-out infinite}
@keyframes dotPulse{0%,100%{opacity:.45}50%{opacity:1}}
.panel{width:min(100%,440px);margin:23px auto 0;padding:20px 16px 18px;border:1px solid rgba(84,186,255,.25);border-radius:25px;background:linear-gradient(145deg,rgba(15,20,29,.96),rgba(3,5,9,.97));box-shadow:0 18px 50px rgba(0,0,0,.55),0 0 30px rgba(22,120,211,.07),inset 0 1px rgba(255,255,255,.05)}
.panel-title{margin:0 0 7px;font-size:12px;font-weight:900;letter-spacing:.2em;color:#e8f5ff}
.panel-sub{margin:0 0 16px;font-size:11px;color:#8799ad}
.status{min-height:42px;display:flex;align-items:center;justify-content:center;gap:9px;margin:0 auto 16px;padding:10px 12px;border:1px solid rgba(84,186,255,.19);border-radius:12px;background:rgba(0,0,0,.38);color:var(--cyan);font-size:12px;font-weight:850;letter-spacing:.08em}
.status-indicator{width:8px;height:8px;flex:0 0 auto;border-radius:50%;background:#9fe4ff;box-shadow:0 0 10px rgba(159,228,255,.7)}
.joystick-wrap{display:flex;justify-content:center;align-items:center;padding:4px 0 10px}
.joystick{position:relative;width:min(70vw,270px);height:min(70vw,270px);max-width:270px;max-height:270px;touch-action:none;user-select:none;-webkit-user-select:none;border-radius:50%;border:1px solid rgba(84,186,255,.58);background:radial-gradient(circle,#172b40 0%,#0d1b2a 47%,#080e17 70%,#03060b 100%);box-shadow:0 0 0 8px rgba(22,120,211,.05),0 0 35px rgba(22,120,211,.13),inset 0 0 25px rgba(0,0,0,.8)}
.joystick:before,.joystick:after{content:"";position:absolute;pointer-events:none;background:rgba(84,186,255,.15)}
.joystick:before{width:1px;height:86%;left:50%;top:7%}.joystick:after{height:1px;width:86%;top:50%;left:7%}
.direction{position:absolute;z-index:1;color:#a1bfd9;font-size:18px;font-weight:900;line-height:1;text-shadow:0 0 8px rgba(84,186,255,.3)}
.direction.up{top:12px;left:50%;transform:translateX(-50%)}.direction.down{bottom:12px;left:50%;transform:translateX(-50%)}.direction.left{left:12px;top:50%;transform:translateY(-50%)}.direction.right{right:12px;top:50%;transform:translateY(-50%)}
.stick{position:absolute;z-index:2;left:50%;top:50%;width:34%;height:34%;transform:translate(-50%,-50%);border-radius:50%;border:2px solid rgba(196,231,255,.85);background:radial-gradient(circle at 32% 25%,#d2efff 0%,#65bfff 20%,#1678d3 60%,#073a69 100%);box-shadow:0 0 0 7px rgba(84,186,255,.07),0 9px 20px rgba(0,0,0,.55),inset 0 2px 5px rgba(255,255,255,.55);transition:box-shadow .12s}
.stick:after{content:"";position:absolute;inset:28%;border:1px solid rgba(255,255,255,.5);border-radius:50%}.stick.active{box-shadow:0 0 0 9px rgba(84,186,255,.12),0 0 25px rgba(84,186,255,.45),0 9px 20px rgba(0,0,0,.55),inset 0 2px 5px rgba(255,255,255,.55)}
.stop{display:block;width:100%;margin:8px auto 0;padding:14px;border:1px solid rgba(255,64,93,.72);border-radius:13px;background:linear-gradient(135deg,#7d1d30,#300b14);color:#fff;font-size:13px;font-weight:950;letter-spacing:.16em;box-shadow:0 5px 0 #1d070c,0 10px 20px rgba(0,0,0,.3);touch-action:manipulation}.stop:active{transform:translateY(3px);box-shadow:0 2px 0 #1d070c}
.tip{margin:16px 2px 0;color:#8796a9;font-size:11px;line-height:1.65}
footer{margin:24px auto 0;color:#8b9bad;font-size:10px;letter-spacing:.04em;line-height:1.7}footer .credit{color:#c0d2e4;letter-spacing:.06em}
@media(min-width:600px){body{padding-top:28px}.panel{padding:24px}.brand-icon{width:82px;height:82px}}
@media(prefers-reduced-motion:reduce){*,*:before,*:after{animation:none!important;transition:none!important}}
</style>
</head>
<body>
<svg class="cyber-mark" viewBox="0 0 600 600" aria-hidden="true" focusable="false">
  <path fill="currentColor" d="M300 42 354 88 411 76 438 125 492 145 474 199 518 240 480 284 493 337 443 361 426 416 369 410 330 459 300 430 270 459 231 410 174 416 157 361 107 337 120 284 82 240 126 199 108 145 162 125 189 76 246 88Z" opacity=".24"/>
  <path d="M166 190 226 154 285 172 326 146 388 166 428 207 388 219 355 203 333 229 365 248 410 242 382 280 337 291 312 327 338 350 378 342 353 380 300 398 247 380 222 342 262 350 288 327 263 291 218 280 190 242 235 248 267 229 245 203 212 219Z" fill="none" stroke="currentColor" stroke-width="13" stroke-linejoin="round" stroke-linecap="round"/>
  <path d="M226 154 206 116 252 135 285 172M388 166 418 130 421 184M337 291 382 280 410 300 381 312M247 380 224 419 276 408 300 398" fill="none" stroke="currentColor" stroke-width="10" stroke-linecap="round"/>
  <circle cx="302" cy="224" r="8" fill="currentColor"/>
  <text x="300" y="515" text-anchor="middle" fill="currentColor" font-family="Arial,sans-serif" font-size="54" font-weight="900" letter-spacing="13">KALI MODE</text>
  <text x="300" y="550" text-anchor="middle" fill="currentColor" font-family="monospace" font-size="16" letter-spacing="5">CYBER CONTROL SYSTEM</text>
</svg>
<header>
  <div class="brand-icon" aria-hidden="true">&gt;_</div>
  <h1>CAR <span>SOCCER</span></h1>
  <div class="subtitle">SISTEMA DE CONTROL ROBÓTICO</div>
  <div class="chip"><i class="dot"></i> INTERFAZ ESP32 ACTIVA</div>
</header>
<main class="panel">
  <h2 class="panel-title">MANDO DIRECCIONAL</h2>
  <p class="panel-sub">Desliza el mando hacia la dirección deseada</p>
  <div class="status" role="status" aria-live="polite"><span class="status-indicator" id="indicator"></span><span id="status">SISTEMA EN ESPERA</span></div>
  <div class="joystick-wrap">
    <div class="joystick" id="joystick" role="application" aria-label="Joystick de movimiento">
      <span class="direction up">▲</span><span class="direction left">◀</span><span class="direction right">▶</span><span class="direction down">▼</span>
      <div class="stick" id="stick"></div>
    </div>
  </div>
  <button class="stop" id="stopButton" type="button">■ &nbsp; FRENAR / DETENER</button>
  <p class="tip">Mantén el dedo sobre el joystick para moverte.<br>Al soltarlo, el robot se detendrá automáticamente.</p>
</main>
<footer>CAR SOCCER · CONTROL INALÁMBRICO · ESP32<br><span class="credit">Diseñado por: Samuel Villanueva C. (© - 2026)</span></footer>
<script>
(function(){
  const pad = document.getElementById('joystick');
  const stick = document.getElementById('stick');
  const status = document.getElementById('status');
  const indicator = document.getElementById('indicator');
  const stopButton = document.getElementById('stopButton');

  let pointerId = null;
  let current = 'stop';
  let lastSent = 0;
  let heartbeat = null;
  let requestChain = Promise.resolve();

  const labels = {
    forward: 'AVANZANDO',
    backward: 'RETROCEDIENDO',
    left: 'GIRO A LA IZQUIERDA',
    right: 'GIRO A LA DERECHA',
    stop: 'MOTORES DETENIDOS'
  };

  // Mantiene las solicitudes en orden para que una orden antigua
  // no llegue después de la orden de detener.
  function sendCommand(command, force) {
    const now = Date.now();
    if (!force && command === current && now - lastSent < 180) return;

    current = command;
    lastSent = now;

    status.textContent = labels[command] || 'SISTEMA EN ESPERA';
    indicator.style.background = command === 'stop' ? '#b8ff5a' : '#35e7ff';
    indicator.style.boxShadow = command === 'stop'
      ? '0 0 10px rgba(184,255,90,.7)'
      : '0 0 10px rgba(53,231,255,.8)';

    requestChain = requestChain
      .catch(function(){})
      .then(function(){
        return fetch('/' + command, {
          method: 'GET',
          cache: 'no-store',
          credentials: 'same-origin'
        });
      })
      .catch(function(){
        status.textContent = 'SIN RESPUESTA DEL ROBOT';
        indicator.style.background = '#ff4768';
        indicator.style.boxShadow = '0 0 10px rgba(255,71,104,.7)';
      });
  }

  function centerStick() {
    stick.style.left = '50%';
    stick.style.top = '50%';
    stick.classList.remove('active');
  }

  function stopHeartbeat() {
    if (heartbeat !== null) {
      clearInterval(heartbeat);
      heartbeat = null;
    }
  }

  function stop() {
    stopHeartbeat();
    pointerId = null;
    centerStick();
    sendCommand('stop', true);
  }

  function move(event) {
    const rect = pad.getBoundingClientRect();
    const cx = rect.left + rect.width / 2;
    const cy = rect.top + rect.height / 2;
    let dx = event.clientX - cx;
    let dy = event.clientY - cy;
    const max = rect.width * 0.31;
    const dist = Math.hypot(dx, dy);

    if (dist > max) {
      dx = dx / dist * max;
      dy = dy / dist * max;
    }

    stick.style.left = 'calc(50% + ' + dx + 'px)';
    stick.style.top = 'calc(50% + ' + dy + 'px)';
    stick.classList.add('active');

    if (Math.hypot(dx, dy) < max * 0.22) {
      sendCommand('stop', true);
      return;
    }

    const angle = Math.atan2(dy, dx) * 180 / Math.PI;
    let command;

    if (angle >= -45 && angle < 45) command = 'right';
    else if (angle >= 45 && angle < 135) command = 'backward';
    else if (angle >= -135 && angle < -45) command = 'forward';
    else command = 'left';

    sendCommand(command, false);
  }

  pad.addEventListener('pointerdown', function(e) {
    e.preventDefault();
    if (pointerId !== null) stop();
    pointerId = e.pointerId;

    try { pad.setPointerCapture(pointerId); } catch (_) {}
    move(e);

    // Repite la última dirección mientras el usuario mantiene presionado.
    // Si deja de llegar el heartbeat, el ESP32 también detendrá los motores.
    stopHeartbeat();
    heartbeat = setInterval(function() {
      if (pointerId !== null && current !== 'stop') {
        sendCommand(current, true);
      }
    }, 250);
  });

  pad.addEventListener('pointermove', function(e) {
    if (e.pointerId === pointerId) {
      e.preventDefault();
      move(e);
    }
  });

  pad.addEventListener('pointerup', function(e) {
    if (e.pointerId === pointerId) stop();
  });

  pad.addEventListener('pointercancel', function(e) {
    if (e.pointerId === pointerId) stop();
  });

  pad.addEventListener('lostpointercapture', function() {
    if (pointerId !== null) stop();
  });

  // Respaldo para navegadores móviles y cuando se pierde el foco.
  window.addEventListener('pointerup', function() {
    if (pointerId !== null) stop();
  });
  window.addEventListener('blur', function() {
    if (pointerId !== null) stop();
  });
  document.addEventListener('visibilitychange', function() {
    if (document.hidden) stop();
  });

  stopButton.addEventListener('click', stop);

  window.addEventListener('pagehide', function() {
    stopHeartbeat();
    fetch('/stop', {
      method: 'GET',
      cache: 'no-store',
      keepalive: true
    }).catch(function(){});
  });
})();
</script>
</body>
</html>
)rawliteral";

// ===== MOVIMIENTO =====
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ===== PAGINA PRINCIPAL =====
void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", html_page);
}

// ===== CONFIGURACION =====
void setup() {
  Serial.begin(115200);
  ultimaOrdenMovimiento = millis();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  stopMotors();
  digitalWrite(LED_AZUL, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando al WiFi");

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi conectado");
    Serial.print("Abre esta direccion en tu celular: http://");
    Serial.println(WiFi.localIP());

    digitalWrite(LED_AZUL, HIGH);
  } else {
    Serial.println();
    Serial.println("No se pudo conectar al WiFi.");
    Serial.println("Verifica el nombre y la clave de la red.");
  }

  server.on("/", HTTP_GET, handleRoot);

  server.on("/forward", HTTP_GET, []() {
    ultimaOrdenMovimiento = millis();
    moveForward();
    server.send(200, "text/plain", "FORWARD");
  });

  server.on("/backward", HTTP_GET, []() {
    ultimaOrdenMovimiento = millis();
    moveBackward();
    server.send(200, "text/plain", "BACKWARD");
  });

  server.on("/left", HTTP_GET, []() {
    ultimaOrdenMovimiento = millis();
    turnLeft();
    server.send(200, "text/plain", "LEFT");
  });

  server.on("/right", HTTP_GET, []() {
    ultimaOrdenMovimiento = millis();
    turnRight();
    server.send(200, "text/plain", "RIGHT");
  });

  server.on("/stop", HTTP_GET, []() {
    ultimaOrdenMovimiento = millis();
    stopMotors();
    server.send(200, "text/plain", "STOP");
  });

  server.begin();
  Serial.println("Servidor web iniciado");
}

// ===== BUCLE PRINCIPAL =====
void loop() {
  server.handleClient();

  // Parada de seguridad: si deja de llegar la señal del joystick,
  // apaga los motores aunque el navegador o el Wi-Fi fallen.
  if (millis() - ultimaOrdenMovimiento > TIEMPO_MAXIMO_SIN_ORDEN) {
    stopMotors();
  }
}
