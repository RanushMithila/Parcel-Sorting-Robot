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

bool readRfid(char address){
  Serial.print("address: ");
  Serial.println(address);
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      Serial.println("Reading real card....");
      rfidCard = String(rfid.serNum[0]) + String(rfid.serNum[1]) + String(rfid.serNum[2]) + String(rfid.serNum[3]);
      if (rfidCard == "240132150" && address == '8'){
        Serial.println("Colombo");
        Serial.println(rfidCard);
        stop();
        return true;
      }else if (rfidCard == "8015945150" && address == '9'){
        Serial.println("Polonnaruwa");
        Serial.println(rfidCard);
        stop();
        return true;
      }else if (rfidCard == "2112081150" && address == '6'){
        Serial.println("Gampaha");
        Serial.println(rfidCard);
        stop();
        return true;
      }else if (rfidCard == "177968228" && address == '5'){
        Serial.println(rfidCard);
        stop();
        return true;
      }else if (rfidCard == "3522329166"){
        Serial.println(rfidCard);
        Serial.println("Couldn't find correct location so dump it in this location.");
        stop();
        return true;
      }
      else{
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


char *getRFID(){
  Serial.println("Reading cards....");
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + String(rfid.serNum[1]) + String(rfid.serNum[2]) + String(rfid.serNum[3]);
      Serial.println(rfidCard.c_str());
      return rfidCard.c_str();
    }
    rfid.halt();
  }
}