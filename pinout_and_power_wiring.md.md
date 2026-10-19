# The Ghost Node — Hardware Wiring & Dual-Power Grid Specification

## ⚡ Dual-Isolated Power Architecture
* **Rail 1 (Raw 3.7V Li-Ion Battery + 1000µF Capacitor):** Dedicated exclusively to powering the SIM800L module to absorb 2A transmission spikes.
* **Rail 2 (Boosted 5.2V via HW-432 Converter):** Safely powers the STM32 Blue Pill, NEO-6M GPS, PIR, and MAX9814 microphone.

## 📌 GPIO Pinout Mapping (`STM32F103C8T6`)
* **SIM800L VCC/GND:** Connected to Rail 1 (3.7V + 1000µF Cap)
* **SIM800L TXD/RXD:** Connected to PA3 (USART2_RX) / PA2 (USART2_TX)
* **NEO-6M GPS TX/RX:** Connected to PA10 (RX1) / PA9 (TX1)
* **PIR Sensor OUT:** Connected to PB0 (Digital In)
* **LDR Tamper Trap:** Connected to PA0 (ADC1_IN0) via 1kΩ pull-down resistor
* **Active Buzzer POS:** Connected to PB1 (Digital Out)