# ⚽ 🚗 Car Soccer - Robot Móvil ESP32 🤖⚡

<div align="center">

![Badge ESP32](https://img.shields.io/badge/Microcontroller-ESP32-blue?style=for-the-badge&logo=espressif)
![Badge WiFi](https://img.shields.io/badge/Connectivity-Wi-Fi_Server-orange?style=for-the-badge&logo=wifi)
![Badge HTML5](https://img.shields.io/badge/UI-HTML5_%2F_%2F_CSS3_%2F_JS-brightgreen?style=for-the-badge&logo=html5)
![Badge Status](https://img.shields.io/badge/Status-Active_%2F_Finished-success?style=for-the-badge)

</div>

Repositorio oficial del proyecto **Car Soccer**, un vehículo robótico móvil controlado de forma inalámbrica mediante un servidor web embebido en un **ESP32**, diseñado e implementado para la **I.E. JEC San Juan Bautista - Huariaca**. 🎓🏆

---

## 🌟 **Descripción del Proyecto**

Este sistema convierte cualquier teléfono celular en un control de mando inalámbrico a través de una red local Wi-Fi. La interfaz web interactiva está alojada directamente en la memoria flash del **ESP32**, permitiendo pilotar el robot en tiempo real mediante un **Joystick táctil de alta precisión**.

---

## 📸 **Galería y Vistas del Proyecto**

| Vista General del Robot | Interfaz de Control |
| :---: | :---: |
| ![Car View Finish](assets/images/car_view_finish.jpg) | ![Control SJB](assets/images/control_sjb.jpg) |

---

## ✨ **Características Principales**

- 📶 **Control Inalámbrico Wi-Fi Directo:** Red local propia alojada en el ESP32 para una respuesta inmediata sin retardos.
- 🕹️ **Joystick Virtual Táctil:** Interfaz fluida desarrollada en HTML5/JS que detecta gestos y ejecuta un **freno de seguridad automático** al soltarlo.
- 🎨 **Diseño Cyber-Futurista & Identidad Institucional:** Interfaz gráfica optimizada con colores neón y la **insignia oficial incrustada** de la I.E. San Juan Bautista.
- ⚡ **Control de Motores PWM:** Regulación de maniobras gracias al driver L298N Mini / MX1508.

---

## 🧰 **Hardware y Componentes Utilizados**

| Componente | Descripción / Modelo |
| :--- | :--- |
| 🧠 **Microcontrolador** | ESP32 DevKit V1 (Wi-Fi integrado) |
| ⚙️ **Driver de Motores** | L298N Mini / MX1508 (Control Puente H) |
| 🔋 **Alimentación** | Batería recargable con regulador de voltaje L7805CV |
| 🤖 **Actuadores** | Motores DC 6V con caja reductora |
| 📐 **Chasis** | Estructura personalizada optimizada |

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

## 💻 **Código Fuente Principal**

Los códigos fuente oficiales se encuentran organizados dentro de la carpeta [src/](src/)[cite: 2]:
* `src/CAR_SOCCER_SJB.ino` (Código principal optimizado con servidor web e IP fija `192.168.10.1`)
* `src/CAR_SOCCER_Kali.ino`
* `src/codigo_local_Sam.ino`
* `src/codigo_local_sjb.ino`

---

<footer>CAR SAN JUAN BAUTISTA • ESP32 LOCALHOST</footer>
