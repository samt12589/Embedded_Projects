#include <Wire.h>

#define SLAVE_ADDR 0x08
#define MIC_PIN A0

int micValue = 0;
int threshold = 512; // Midpoint for 10-bit ADC (0–1023)

void setup() {
  pinMode(MIC_PIN, INPUT);
  Wire.begin(SLAVE_ADDR);        // Join I2C bus as slave
  Wire.onRequest(requestEvent);  // Define what to do when master asks
  Serial.begin(9600);
  Serial.println("Nano ready as I2C Slave (0x08)");
}

void loop() {
  // Continuously read microphone
  micValue = analogRead(MIC_PIN);
  delay(10); // Small stabilization delay
}

// Called when master requests data
void requestEvent() {
  byte level = (micValue > threshold) ? 1 : 0; // 1 = High (loud), 0 = Low
  Wire.write(level); // Send single byte back
  Serial.print("Mic value: ");
  Serial.print(micValue);
  Serial.print(" -> Sent: ");
  Serial.println(level);
}
