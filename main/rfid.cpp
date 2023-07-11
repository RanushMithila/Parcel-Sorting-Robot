#include "rfid.h"
#include "move.h"
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);

String rfidCard;

void setupRfid(){
	Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
}

bool readRfid(char *address){
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + String(rfid.serNum[1]) + String(rfid.serNum[2]) + String(rfid.serNum[3]);
      if (rfidCard == "240132150" && address == "Colombo"){
        Serial.println(rfidCard);
        stop();
        return true;
      }else if (rfidCard == "8015945150" && address == "Polonnaruwa"){
        Serial.println(rfidCard);
        stop();
        return true;
      }else{
        Serial.println(rfidCard);
        return false;
      }
    }else{
      return false;
    }
    rfid.halt();
  }else{
    return false;
  }
}