
// ==========================================
// THE GHOST NODE — EVENT-DRIVEN STM32 FIRMWARE
// Autonomous Stealth Tracker & Surveillance Node
// Developer: Aditya Kumar Gupta (aditya.geninfo.in)
// ==========================================

#include <TinyGPS++.h>

#define PIR_PIN     PB0
#define BUZZER_PIN  PB1
#define LDR_PIN     PA0
#define AUDIO_TRIG_PIN PB4 // Digital sound threshold trigger from INMP441 mic
#define TAMPER_THRESHOLD 1800 

TinyGPSPlus gps;
HardwareSerial SerialGPS(PA10, PA9);  // USART1: NEO-6M GPS
HardwareSerial SerialGSM(PA3, PA2);   // USART2: SIM900A GSM

const char ADMIN_PHONE[] = "+919411247540";
bool tamperTriggered = false;
unsigned long lastPirAlert = 0;
unsigned long lastCallAlert = 0;

void sendSMS(String message) {
  SerialGSM.println("AT+CMGF=1");
  delay(300);
  SerialGSM.print("AT+CMGS=\"");
  SerialGSM.print(ADMIN_PHONE);
  SerialGSM.println("\"");
  delay(300);
  SerialGSM.print(message);
  delay(100);
  SerialGSM.write(26); // CTRL+Z to send SMS
  delay(3000);
}

void makePhoneCall() {
  SerialGSM.print("ATD");
  SerialGSM.print(ADMIN_PHONE);
  SerialGSM.println(";");
  delay(10000); // Ring for 10 seconds for live audio listening
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(AUDIO_TRIG_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT_ANALOG);
  digitalWrite(BUZZER_PIN, LOW);

  SerialGPS.begin(9600);
  SerialGSM.begin(9600);
  delay(3000);

  SerialGSM.println("AT");
  delay(200);
}

void loop() {
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  String currentLoc = gps.location.isValid() ? 
    String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) : "Acquiring GPS Fix";

  // 1. ACTIVE ANTI-TAMPER TRAP (LDR Light Sensor)
  if (analogRead(LDR_PIN) > TAMPER_THRESHOLD && !tamperTriggered) {
    tamperTriggered = true;
    digitalWrite(BUZZER_PIN, HIGH);
    sendSMS("CRITICAL TAMPER ALERT! Enclosure Opened! GPS: https://maps.google.com/?q=" + currentLoc);
  }

  // 2. PIR MOTION SENSOR -> AUTOMATIC SMS ALERT
  if (digitalRead(PIR_PIN) == HIGH && (millis() - lastPirAlert > 60000)) {
    lastPirAlert = millis();
    sendSMS("MOTION DETECTED! Zone breached. GPS: https://maps.google.com/?q=" + currentLoc);
  }

  // 3. INMP441 SOUND THRESHOLD -> AUTOMATIC PHONE CALL FOR LIVE LISTENING
  if (digitalRead(AUDIO_TRIG_PIN) == HIGH && (millis() - lastCallAlert > 120000)) {
    lastCallAlert = millis();
    makePhoneCall(); 
  }
}
