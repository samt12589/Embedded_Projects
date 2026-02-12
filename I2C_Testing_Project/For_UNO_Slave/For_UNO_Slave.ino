#include <Wire.h>

#define SLAVE_ADDR 0x09
#define LED_PIN 13 // Built-in LED (D13)

volatile byte blinkCommand = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Off by default (active low)
  
  Wire.begin(SLAVE_ADDR);        // Join I2C bus as slave
  Wire.onReceive(receiveEvent);  // Handler for incoming data

  Serial.begin(9600);
  Serial.println("UNO ready as I2C Slave (0x09)");
}

void loop() {
  if (blinkCommand == 1) {
    // Fast blink for loud
    digitalWrite(LED_PIN, LOW);
    delay(200);
    digitalWrite(LED_PIN, HIGH);
    delay(200);
  } else {
    // Slow blink for quiet
    digitalWrite(LED_PIN, LOW);
    delay(800);
    digitalWrite(LED_PIN, HIGH);
    delay(800);
  }
}

// Called when master sends data
void receiveEvent(int howMany) {
  if (Wire.available()) {
    blinkCommand = Wire.read(); // Expecting 0 or 1
    Serial.print("Received blinkCommand: ");
    Serial.println(blinkCommand);
  }
}
