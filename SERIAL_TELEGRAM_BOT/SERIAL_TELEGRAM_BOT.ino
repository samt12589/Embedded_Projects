#include <TelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

int var;

const char* ssid = "YOUR WIFI NAME"; // Add your info if needed
const char* password = "WIFI PASSWORD";

const char BotToken[] =  "*"; // Removed Token for security reasons
WiFiClientSecure net_ssl; 
TelegramBot bot (BotToken, net_ssl);

const char* CHAT_ID = "*" ; // get from telegram , Removed for security reasons
char* chat_id ;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

// Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  bot.begin();
  delay(1000);

 
}

void loop() {
  message m = bot.getUpdates();
  // put your main code here, to run repeatedly:
if( m.text.equals("/Start")){
  Serial.println("hello");

  var = Serial.parseInt(); // reading serial communication
  
  Serial.println(var);

 if (var == 1 ){
  bot.sendMessage(m.chat_id, "User: Saksham Kumar entered");
 }
 else if (var == 2 ){
  bot.sendMessage(m.chat_id, "Wrong ID CARD PLEASE BE SAFE!");
 }
 else 
   bot.sendMessage(m.chat_id, "Nobody Came home");}
   yield();
}
