#include <SPI.h>
#include <MFRC522.h>
#include <RFID.h>
#include "pitches.h"
// plan: small screen display- swipe card, you swipe the card, enter code, enter the code, if either is wrong itll beep and say no but if its all right then unlock


#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above

RFID rfid(SS_PIN, RST_PIN);//no idea what this does

String rfidCard;// string

void setup(){
  Serial.begin(9600);// serial for reference
  Serial.println("Starting the RFID reader");
  SPI.begin();
  rfid.init();
  pinMode(8,OUTPUT);// connected to buzzer
}

void loop(){
  if (rfid.isCard()){// if theres a card?
    if (rfid.readCardSerial()){
      rfidCard = String(rfid.serNum[0])+ " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);//set the string as the card serial number
      Serial.println(rfidCard);
      if (rfidCard == "58 202 81 60"){ //if its my card then play a nice tone and eventually unlock something
        tone(8, NOTE_A5, 300);
        delay(100);
        tone(8, NOTE_D5, 300);
        delay(100);
        tone(8, NOTE_G5, 300);
        delay(100);
        Serial.println("Access Granted");
      }else{// elif its not my card BEEP BEEP BEEP and no unlock
        tone(8, NOTE_A5, 100);
        delay(200);
        tone(8, NOTE_A5, 100);
        delay(200);
        tone(8, NOTE_A5, 100);
        delay(200);
        Serial.println("Access Denied");
      }
    }
    rfid.halt();
  }
}
