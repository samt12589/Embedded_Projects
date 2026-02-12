#include <SoftwareSerial.h>

SoftwareSerial nanoSerial(14, 12); // TX, RX to Nano, 
                                    // D5 NodeMCU -> D3 Nano
                                    // D6 NodeMCU -> D2 Nano
void setup() {
  Serial.begin(9600);        // USB for PC
  nanoSerial.begin(9600);    // UART to Nano
  Serial.println("Type HIGH or LOW to send to Nano:");
}

void loop() {
  // --- Read from PC and send to Nano ---
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "HIGH" || cmd == "LOW") {
      nanoSerial.println(cmd);        // send to Nano
      Serial.println("Sent to Nano: " + cmd);
    } else {
      Serial.println("Invalid command. Use HIGH or LOW.");
    }
  }

  // --- Read feedback from Nano ---
  if (nanoSerial.available()) {
    String feedback = nanoSerial.readStringUntil('\n');
    feedback.trim();
    if (feedback.length() > 0) {
      delay(1500);
      Serial.println("Received from Nano: " + feedback + ". Sorry man , just having fun!");
      nanoSerial.println(feedback);
      Serial.println("Sent to Nano: " + feedback + ". Here you go!");
    }
  }
}
