# 🛰️ The Ghost Node — Autonomous Multi-Sensory Stealth Tracker & Surveillance System

> An independent, cellular-and-satellite-backed covert monitoring device designed for asset tracking, security, and event-driven anti-tamper surveillance without relying on Wi-Fi or nearby smartphones.

[![Status](https://img.shields.io/badge/Status-Production_Ready-emerald?style=for-the-badge)]()
[![MCU](https://img.shields.io/badge/MCU-STM32F103C8T6-blue?style=for-the-badge)]()

---

## 🎯 The Main Motive & Event-Driven Logic
The primary motive of **The Ghost Node** is to build a fully autonomous, stealthy, and event-driven surveillance node that functions as an intelligent trigger system:
1. **PIR Motion Sensor ➔ Automatic SMS Alert:** Detects human presence and instantly sends an SMS with live GPS coordinates.
2. **INMP441 Digital Microphone ➔ Automatic Phone Call:** Monitors sound levels and automatically places a direct phone call via the SIM900A module for live acoustic eavesdropping during a disturbance.
3. **NEO-6M GPS Module ➔ Live Satellite Tracking:** Continuous global location tracking.
4. **LDR Light Trap ➔ Enclosure Tamper Alert:** Fires an instant SMS if the security box is opened.

---

## 🛠️ Bill of Materials (BOM)
| Component | Specification / Role |
| :--- | :--- |
| **STM32 Blue Pill (`STM32F103C8T6`)** | ARM Cortex-M3 72MHz Core (Main System Brain) |
| **SIM900A GSM Module** | Cellular SMS alerts & automated voice calls |
| **NEO-6M GPS Module** | Satellite real-time coordinate tracking |
| **INMP441 Digital Microphone** | Sound level monitoring & auto-call trigger |
| **PIR Motion Sensor** | Infrared human movement tripwire |
| **LDR + 1kΩ Resistor** | Voltage-divider light trap for enclosure tamper detection |
| **Active Buzzer** | Remote acoustic alarm / locator beacon |
| **Power System** | 3.7V 3000mAh Li-Ion + TP4056 + HW-432 5.2V Boost + 1000µF Capacitor |

---

## 📂 Repository Structure
```text
📂 ghost-node
├── 📂 firmware             <-- STM32 C++ source code (ghost_node_stm32.ino)
├── 📂 schematics           <-- Wiring & dual-power specifications
└── 📄 README.md            <-- Project documentation