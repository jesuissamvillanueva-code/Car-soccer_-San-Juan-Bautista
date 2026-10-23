# ⚽ 🚗 **Car Soccer - Robot Móvil ESP32** 🤖⚡

<div align="center">

![Badge ESP32](https://img.shields.io/badge/Microcontroller-ESP32-blue?style=for-the-badge&logo=espressif)
![Badge WiFi](https://img.shields.io/badge/Connectivity-Wi-Fi_Server-orange?style=for-the-badge&logo=wifi)
![Badge HTML5](https://img.shields.io/badge/UI-HTML5_%2F_%2F_CSS3_%2F_JS-brightgreen?style=for-the-badge&logo=html5)
![Badge Status](https://img.shields.io/badge/Status-Active_%2F_Finished-success?style=for-the-badge)

</div>

Repositorio oficial del proyecto **Cas Soccer**, un vehículo robótico móvil y autónomo controlado de forma inalámbrica a través de un servidor web embebido en un **ESP32**, diseñado e implementado con orgullo para la **I.E. San Juan Bautista - Huariaca**. 🎓🏆

---

## 🌟 **Descripción del Proyecto**

Este sistema innovador convierte un teléfono celular en un control de mando inalámbrico mediante una red local Wi-Fi. La interfaz web está alojada directamente dentro de la memoria flash del **ESP32**, lo que permite pilotar el robot en tiempo real desde cualquier smartphone o tablet con navegador web utilizando un **Joystick táctil interactivo** de alta precisión.

---

## ✨ **Características Principales**

* 📶 **Control Inalámbrico Wi-Fi Directo:** El microcontrolador gestiona la conexión de red para una respuesta inmediata sin retardos.
* 🕹️ **Joystick Virtual Táctil Inteligente:** Interfaz fluida desarrollada en HTML5/JS que detecta gestos táctiles (Touch/Mouse) y regresa automáticamente al centro ejecutando un **freno de seguridad** al soltarlo.
* 🎨 **Diseño Cyber-Futurista & Identidad Institucional:** Interfaz gráfica optimizada con colores neón (`#00f0ff`), efectos de luz ambiental y la **insignia oficial incrustada** de la I.E. San Juan Bautista.
* ⚡ **Control de Motores PWM Avanzado:** Regulación de velocidad y maniobras de giro diferencial gracias al uso eficiente del Driver L298N Mini / MX1508.

---

## 🧰 **Hardware y Componentes Utilizados**

| Componente | Descripción / Modelo |
| :--- | :--- |
| 🧠 **Microcontrolador** | ESP32 DevKit V1 (Wi-Fi / Bluetooth integrado) |
| ⚙️ **Driver de Motores** | L298N Mini / MX1508 (Control Puente H) |
| 🔋 **Alimentación** | Batería recargable con regulador de voltaje L7805CV |
| 🤖 **Actuadores** | Motores DC 6V con caja reductora (Tracción diferencial) |
| 📐 **Chasis** | Diseño estructural personalizado y optimizado |

---

## 📌 **Esquema de Conexiones (Pinout del ESP32)**

| Pin GPIO ESP32 | Conexión del Hardware | Función Principal |
| :---: | :--- | :--- |
| **GPIO 16** | Driver IN1 | Control de dirección Motor A |
| **GPIO 17** | Driver IN2 | Control de dirección Motor A |
| **GPIO 18** | Driver IN3 | Control de dirección Motor B |
| **GPIO 19** | Driver IN4 | Control de dirección Motor B |
| **GPIO 2** | LED Azul Interno | Indicador visual de estado y conexión Wi-Fi |

---

## 💻 **Instrucciones de Instalación y Uso**

### 1️⃣ Preparación del Entorno
1. Asegúrate de tener instalado el [Arduino IDE](https://www.arduino.cc/en/software).
2. Instala el soporte para placas **ESP32** en el gestor de tarjetas.

### 2️⃣ Clonar o Descargar el Código
* Descarga el código fuente de este repositorio y ábrelo con tu Arduino IDE.

### 3️⃣ Configurar las Credenciales de Red
Busca las siguientes líneas en el código e introduce los datos de tu red Wi-Fi (o la red compartida desde tu celular):
```cpp
const char* ssid = "Tu_Red_WiFi";
const char* password = "Tu_Contraseña";
