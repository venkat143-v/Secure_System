#include <SoftwareSerial.h>

#define PIR_PIN 2  // PIR sensor connected to digital pin 2
SoftwareSerial gsmSerial(7, 8);  // RX, TX for GSM module

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(PIR_PIN, INPUT);

  // Initialize GSM module
  initializeGSM();
}

void loop() {
  // Read PIR sensor
  int pirValue = digitalRead(PIR_PIN);

  if (pirValue == HIGH) {
    Serial.println("Motion detected!");

    // Send SMS
    sendSMS("+1234567890", "Intruder detected!");

    delay(10000);  // Wait for 10 seconds to avoid multiple alerts
  }
}

void initializeGSM() {
  delay(1000);
  gsmSerial.println("AT");  // Check if the GSM module is responding
  delay(1000);

  gsmSerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);

  gsmSerial.println("AT+CNMI=2,2,0,0,0");  // New SMS message indications
  delay(1000);

  Serial.println("GSM module initialized");
}

void sendSMS(const char* phoneNumber, const char* message) {
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");

  delay(1000);

  gsmSerial.println(message);
  gsmSerial.write(26);  // Ctrl+Z to end the SMS
  delay(1000);

  Serial.println("SMS sent");
}
