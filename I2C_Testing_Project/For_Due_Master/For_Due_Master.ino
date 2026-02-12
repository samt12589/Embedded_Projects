#include <Wire.h>

#define NANO_ADDR   0x08
#define UNO_ADDR 0x09

void setup() {
  Wire.begin(); // Start I2C as master
  Serial.begin(9600);
  Serial.println("Due ready as I2C Master");
}

void loop() {
  // Step 1: Request microphone level from Nano
  Wire.requestFrom(NANO_ADDR, 1); // Request 1 byte
  if (Wire.available()) {
    byte micLevel = Wire.read();
    Serial.print("Mic Level received from Nano: ");
    Serial.println(micLevel);

    // Step 2: Send that mic level to UNO
    Wire.beginTransmission(UNO_ADDR);
    Wire.write(micLevel); // 0 = low, 1 = high
    Wire.endTransmission();
    Serial.print("Sent to UNO: ");
    Serial.println(micLevel);
  }

  delay(500); // Poll every 0.5s
}
