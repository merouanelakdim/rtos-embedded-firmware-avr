# RTOS Embedded Firmware – Event‑Driven LED Controller (FreeRTOS + AVR)
![Embedded](https://img.shields.io/badge/Field-Embedded%20Systems-darkgreen)
![ArduinoIDE](https://img.shields.io/badge/IDE-Arduino-teal)
![PlatformIO](https://img.shields.io/badge/Build-PlatformIO-orange)
![HAL](https://img.shields.io/badge/Driver-Hardware%20Abstraction-blue)
![StateMachine](https://img.shields.io/badge/Design-State%20Machine-informational)
![Firmware](https://img.shields.io/badge/Firmware-Low%20Level-black)
![Interrupt](https://img.shields.io/badge/Design-Interrupt%20Driven-important)
![RealTime](https://img.shields.io/badge/Real--Time-System-critical)
![MCU](https://img.shields.io/badge/MCU-ATmega328P-blueviolet)


## 📌 Project Title

**Event‑Driven Embedded Firmware using FreeRTOS on AVR (Arduino UNO) with ISR Notifications and Hardware Driver Abstraction**

---

## 🎯 Project Overview

This project demonstrates a professional embedded firmware architecture using **C language**, **FreeRTOS**, **hardware interrupts**, and a **state machine design** running on an **Arduino UNO (AVR)** microcontroller.

The firmware controls LEDs through a **74HC595 shift register** while implementing real‑time design patterns used in modern embedded systems such as industrial IoT devices, robotics platforms, and automotive ECUs.

The goal of this project is to showcase strong competencies in:

* Low‑level microcontroller programming
* Real‑time operating systems (RTOS)
* Interrupt‑driven embedded design
* Hardware abstraction layer (HAL) concepts
* Deterministic firmware architecture

---

## 🧠 Technical Concepts Demonstrated

### ✔ FreeRTOS Task Scheduling

* Real‑time task management
* Priority‑based scheduling
* Blocking mechanisms using RTOS notifications

### ✔ Hardware Interrupts (ISR)

* Timer1 hardware configuration via AVR registers
* Interrupt Service Routine design rules
* ISR‑to‑Task communication using RTOS API

### ✔ Event‑Driven Architecture

* Timer interrupt triggers system events
* Tasks wake only when required
* CPU usage optimization

### ✔ State Machine Firmware Design

System states:

* INIT
* IDLE
* RUNNING
* UPDATE_LED

Provides deterministic and maintainable logic flow.

### ✔ Hardware Driver Layer

* Direct GPIO control
* Shift register communication
* Separation between logic and hardware

---

## 🧱 System Architecture

```
[TIMER1 Hardware Interrupt]
            │
            ▼
        [ISR Handler]
            │
            ▼
[FreeRTOS Task Notification Mechanism]
            │
            ▼
     [State Machine Task]
            │
            ▼
      [HAL Driver Layer]
            │
            ▼
        [74HC595 IC]
            │
            ▼
            LEDs
```

---

## ⚙️ Hardware Requirements

* Arduino UNO R3 (ATmega328P)
* 74HC595 Shift Register IC
* LEDs + Resistors
* Breadboard + Jumper Wires

---

## 💻 Software Requirements

* PlatformIO (recommended) or Arduino IDE
* FreeRTOS AVR Port
* C Compiler (AVR-GCC via PlatformIO)

---

## 🚀 Features Implemented

* Timer1 hardware interrupt configuration
* ISR safe RTOS notification
* Event‑driven task execution
* Deterministic firmware state machine
* LED sequencing via shift register
* Separation between application logic and hardware layer

---

## 🧪 How to Build and Run

1. Clone the repository:

```
git clone <REPO_URL>
```

2. Open project in PlatformIO

3. Connect Arduino UNO via USB

4. Build and upload firmware

5. Observe LED pattern controlled by RTOS task

---

## 📂 Project Structure

```
/src
 ├── main.c
 ├── state_machine.c
 ├── shift_register_driver.c
/include
 ├── state_machine.h
 ├── shift_register_driver.h
```

---

## 📈 Skills Demonstrated for Embedded Engineering Roles

* Embedded C Programming
* Real‑Time Systems (RTOS)
* Interrupt‑Driven Firmware
* Hardware Register Configuration
* Embedded Software Architecture
* Low‑Level Driver Development
* Deterministic System Design

---

## 🔮 Future Improvements

* Watchdog Timer integration
* RTOS Queues and Event Groups
* UART debugging interface
* Scheduler runtime monitoring
* Hardware abstraction layer expansion
* Unit testing for drivers

---

## 👨‍💻 Author

Embedded Software Engineer – Real‑Time Systems & Low‑Level Firmware Development

Portfolio: https://www.lakdim.com/
Linkedin : https://www.linkedin.com/in/merouane-lakdim-0a92861b3/

---

## 📜 License

MIT License – Free to use and modify for educational and professional purposes.
