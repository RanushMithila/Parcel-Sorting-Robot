#include "rfid.h"
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);

String rfidCard;

void setupRfid(){
	Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
}

bool readRfid(String address){
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + String(rfid.serNum[1]) + String(rfid.serNum[2]) + String(rfid.serNum[3]);
      if (rfidCard == "240132150" && address == "Colombo"){
        return true;
      }else if (rfidCard == "8015945150" && address == "Polonnaruwa"){
        return true;
      }else{
        return false;
      }
      Serial.println(rfidCard);
    }
    rfid.halt();
  }
}