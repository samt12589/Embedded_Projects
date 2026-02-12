// NodeMCU Light Controller with Web Interface and UDP Commands
// Designed for 3 zones (2 lights in one room), using mDNS for local access

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>

const char* ssid = "TEST-2.4";
const char* password = "Saksham@TEST";

WiFiUDP udp;

// Light IPs (update these with your specific IP addresses)
IPAddress RoomALight1(192, 168, 0, 216); // RoomA Light 1
IPAddress RoomALight2(192, 168, 0, 215); // RoomA Light 2
IPAddress corridorLight(192, 168, 0, 237); // Corridor
IPAddress SakshamLight(192, 168, 0, 171); // RoomB

const unsigned int lightPort = 38899; // Default port for WiZ lights

// UDP Commands
const char* onCmd = "{\"method\":\"setState\",\"params\":{\"state\":true}}";
const char* offCmd = "{\"method\":\"setState\",\"params\":{\"state\":false}}";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());

  // Start mDNS responder
  if (MDNS.begin("lights")) {
    Serial.println("mDNS responder started: http://lights.local");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.begin();
}

void loop() {
  MDNS.update();

  WiFiClient webClient = server.available();
  if (webClient) {
    String request = webClient.readStringUntil('\r');
    webClient.readStringUntil('\n');
    Serial.println("Request: " + request);

    // Handle light controls
    if (request.indexOf("GET /") >= 0) {
      if (request.indexOf("/room/on") >= 0) {
        sendUDP(RoomALight1, onCmd);
        sendUDP(RoomALight2, onCmd);
      }
      if (request.indexOf("/room/off") >= 0) {
        sendUDP(RoomALight1, offCmd);
        sendUDP(RoomALight2, offCmd);
      }
      if (request.indexOf("/corridor/on") >= 0) sendUDP(corridorLight, onCmd);
      if (request.indexOf("/corridor/off") >= 0) sendUDP(corridorLight, offCmd);
      if (request.indexOf("/myroom/on") >= 0) sendUDP(SakshamLight, onCmd);
      if (request.indexOf("/myroom/off") >= 0) sendUDP(SakshamLight, offCmd);
    }

    // Serve the custom HTML page
    String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<title>Smart Light Control</title>";
    html += "<style>body{font-family:sans-serif;text-align:center;background-color:black;color:white;margin:0;padding:0;}h2{margin-top:20px;font-size:2em;}";
    html += ".room{margin:30px 0;}button{padding:20px 40px;font-size:1.5em;border:2px solid white;border-radius:8px;background-color:#444;color:white;margin:10px;cursor:pointer;transition:background-color 0.3s,transform 0.3s;}";
    html += "button:hover{background-color:#666;transform:scale(1.1);}button.on{background-color:#4CAF50;}button.off{background-color:#f44336;}button:active{transform:scale(0.95);}</style></head><body>";
    
    html += "<h2>Wiz Light Control</h2>";
    html += genRoom("RoomA's Room", "room");
    html += genRoom("Corridor", "corridor");
    html += genRoom("Saksham's Room", "myroom");

    html += "<script>function controlLights(room, state){fetch('/'+room+'/'+state).then(()=>{document.querySelectorAll('[data-room=\"'+room+'\"]').forEach(b=>b.classList.remove('on','off'));document.getElementById(room+'-'+state).classList.add(state);});}</script>";
    html += "</body></html>";

    webClient.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
    webClient.print(html);
    delay(1);
    webClient.stop();
  }
}

String genRoom(String label, String id) {
  return "<div class='room'><h3>" + label + "</h3>" +
         "<button id='" + id + "-on' class='on' data-room='" + id + "' onclick=\"controlLights('" + id + "','on')\">Turn On</button>" +
         "<button id='" + id + "-off' class='off' data-room='" + id + "' onclick=\"controlLights('" + id + "','off')\">Turn Off</button></div>";
}

void sendUDP(IPAddress ip, const char* message) {
  udp.beginPacket(ip, lightPort);
  udp.write(message);
  udp.endPacket();
}
