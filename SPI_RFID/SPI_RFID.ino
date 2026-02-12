#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(10, 5);
int green = 8;
int red = 11;
int yellow = 9;
String tagUID = "23 09 7B 3E";

void setup() {
  // put your setup code here, to run once:

pinMode(green, OUTPUT);
pinMode(red, OUTPUT);
pinMode(yellow, OUTPUT);
  
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();

  Serial3.begin(115200);
  
}

void loop() {
  digitalWrite(yellow, HIGH);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //Reading from the card
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();
  
   
    
  //Checking the card
  if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access 
  {
    Serial3.println(1);
    // representing lock
    digitalWrite(yellow,LOW); 
    digitalWrite(green, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
  }

  else
  {
    Serial3.println(2);
   digitalWrite(yellow,LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(red, LOW);
  }

}
