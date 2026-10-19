# The Ghost Node — Hardware Wiring & Event-Driven Architecture Specification

## 🎯 Event-Driven Action Summary
* **PIR Motion Trigger (`PB0`)** ➔ Automatically fires an **SMS alert** with live Google Maps GPS coordinates.
* **INMP441 Sound Trigger (`PB4`)** ➔ Automatically **places a phone call** via the SIM900A module to the owner for live acoustic eavesdropping.
* **LDR Tamper Trap (`PA0`)** ➔ Fires an instant **Critical Tamper SMS** if the enclosure is opened.

---

## ⚡ Dual-Isolated Power Architecture
To prevent the `SIM900A GSM` module's high current transmission spikes from resetting the microcontroller, power is isolated into two distinct rails:
* **Rail 1 (Raw 3.7V Li-Ion Battery + 1000µF Electrolytic Capacitor):** Directly powers the `SIM900A` module to handle cellular power surges.
* **Rail 2 (Boosted 5.2V via HW-432 Converter):** Safely powers the `STM32 Blue Pill`, `NEO-6M GPS`, `INMP441`, and `PIR` sensor.

---

## 📌 Complete GPIO Pinout Mapping (`STM32F103C8T6`)

| Component | Component Pin | STM32 Blue Pill Pin / Power Rail | Function / Event Role |
| :--- | :--- | :--- | :--- |
| **SIM900A GSM Module** | `VCC` / `GND` | **Rail 1: 3.7V Bat (+)** + `1000µF Cap` | Burst-Protected Cellular Power Supply |
| **SIM900A GSM Module** | `TXD` / `RXD` | `PA3 (USART2_RX)` / `PA2 (USART2_TX)` | AT Commands for SMS (`AT+CMGS`) & Voice Calls (`ATD`) |
| **NEO-6M GPS Module** | `VCC` / `TX` / `RX` | **Rail 2: 5.2V** / `PA10 (RX1)` / `PA9 (TX1)` | Satellite NMEA Coordinate Stream |
| **INMP441 Digital Mic** | `SD / WS / SCK` | Digital Signal Processing / `PB4 (Trigger Out)` | Sound Level Monitoring & Auto-Call Trigger |
| **PIR Motion Sensor** | `VCC` / `OUT` | **Rail 2: 5.2V** / `PB0 (Digital In)` | Human Motion Detection (Sends SMS) |
| **LDR Tamper Trap** | `Divider Node` | `PA0 (ADC1_IN0)` via `1kΩ` Pull-Down | Enclosure Open / Tamper Alarm |
| **Active Buzzer** | `POS (+)` | `PB1 (Digital Out)` | Remote Locator Beacon / Alarm |
