#include <WiFi.h>
#include <HardwareSerial.h>

const char* ssid = "TEST-2.4";
const char* password = "Saksham@TEST";

WiFiServer server(80);

HardwareSerial nanoSerial(1); // RX=16, TX=17 or adjust pins

String dataLine = "";

void setup() {
  Serial.begin(115200);
  nanoSerial.begin(115200, SERIAL_8N1, 16, 17); // RX, TX pins
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (nanoSerial.available()) {
        dataLine = nanoSerial.readStringUntil('\n');
        // Send to web client
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE html><html><head><title>Power Monitor</title>");
        client.println("<script src='https://cdn.jsdelivr.net/npm/chart.js'></script></head><body>");
        client.println("<h2>DC/DC Power Monitor</h2>");
        client.println("<pre>" + dataLine + "</pre>");
        client.println("</body></html>");
        break;
      }
    }
    delay(1);
    client.stop();
  }
}
