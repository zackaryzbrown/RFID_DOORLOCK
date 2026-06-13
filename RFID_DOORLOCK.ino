#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 myRFID(SS_PIN, RST_PIN);

int pinLEDRed=2;
int pinLEDGreen=7;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  myRFID.PCD_Init();
  pinMode(pinLEDRed, OUTPUT);
  pinMode(pinLEDGreen, OUTPUT);
}

void loop() {
  if(!myRFID.PICC_IsNewCardPresent()){
    return;
    }
  if(! myRFID.PICC_ReadCardSerial()){
    return;
    }

  Serial.println("USER ID tag :");
  String content="";
  for (byte i = 0; i < myRFID.uid.size; i++) {
      Serial.println(myRFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.println(myRFID.uid.uidByte[i], HEX);
      content.concat(String(myRFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(myRFID.uid.uidByte[i], HEX));
  }
  delay(500);
  Serial.println();

  
  Serial.print("Message : ");
  content.toUpperCase();
  if(content.substring(1) == "43 02 78 1A"){
    Serial.println("Access Granted!");
    digitalWrite(pinLEDGreen,HIGH);
    Serial.println();
    delay(2000);
    digitalWrite(pinLEDGreen,LOW);
  }
  else{
    digitalWrite(pinLEDRed,HIGH);
    Serial.println("Access Denied!");
    delay(2000);
    digitalWrite(pinLEDRed, LOW);
   }
}
