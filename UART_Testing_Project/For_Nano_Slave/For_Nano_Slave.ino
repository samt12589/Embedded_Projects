#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3); // RX, TX from NodeMCU
                          // D5 NodeMCU -> D3 Nano
                          // D6 NodeMCU -> D2 Nano

void setup() {
  pinMode(13, OUTPUT);       // onboard LED
  esp.begin(9600);           // UART from NodeMCU
  Serial.begin(9600);        // USB Serial monitor
  Serial.println("Nano UART ready...");
}

void loop() {
  if (esp.available()) {
    String cmd = esp.readStringUntil('\n');
    cmd.trim();

    if (cmd == "HIGH") {
      digitalWrite(13, HIGH);
      Serial.println("LED is HIGH");  // USB feedback

      delay(2000);                    // wait 2 sec

      esp.println("LOW");             // send back to NodeMCU
      
      Serial.println("Hey! Cut it out!!");   // USB feedback

      //digitalWrite(13, LOW);

    } else if (cmd == "LOW") {
      delay(1000);   // wait 1 sec
      digitalWrite(13, LOW);
      Serial.println("LED set to LOW by NodeMCU, Thanks!");
    } else {
      Serial.println("Unknown command: " + cmd);
    }
  }
}
