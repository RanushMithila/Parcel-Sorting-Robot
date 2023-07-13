#include "dataTransfer.h"

SoftwareSerial arduinoSerial(4, 5);  // RX, TX pins connected to ESP32

void setupDataTransfer(){
  // Serial.begin(115200);  // Serial monitor for debugging
  arduinoSerial.begin(115200);  // Serial communication with ESP32
}


// char *getQRData(){
//   if (arduinoSerial.available()) {
//     char receivedData;
//     // while (arduinoSerial.available()) {
//         // receivedData = (char)arduinoSerial.read();  // Read data from the Esp32
//         receivedData = arduinoSerial.read();  // Read data from the Esp32
//     // }
//     // int data = receivedData.toInt();  // Convert the received string to an integer
//     Serial.print("Received data: ");
//     Serial.println(receivedData);
//     if (strcmp(receivedData,"Polonnaruwa") != 0){
//       Serial.println("Not correct data");
//       getQRData();
//     }
//     delay(2000);
//     // return receivedData.c_str();
//     return receivedData;
//   }else{
//     Serial.println("Serial not available");
//     getQRData();
//   }
//   // return receivedData;
//   delay(500);
// }


// void getQRData(char &city){
//   if(arduinoSerial.available()){
//     delay(1000);
//     char data = arduinoSerial.read();
//     delay(800);
//     Serial.print("Data Received: ");
//     Serial.println(data);
//     if (data == '9' || data == '8' || data == '7' || data == '6'){
//       Serial.println("Correct data");
//       city = data;
//       arduinoSerial.flush();
//     }else{
//       city = '0';
//     }
//   }else{
//   city = '0';
//   }
//   delay(500);
//   arduinoSerial.flush();
// }

void getQRData(char& city) {
  if (arduinoSerial.available()) {
    arduinoSerial.flush();
    char data = arduinoSerial.read();
    Serial.print("Data Received: ");
    Serial.println(data);
    
    switch (data) {
      case '9':
      case '8':
      case '7':
      case '6':
        Serial.println("Correct data");
        Serial.print("data: ");
        Serial.print(data);
        Serial.print("\tcity: ");
        Serial.println(city);
        if (strcmp(data,city) == 0){
          Serial.println("Old data");
          city = '3';
        }else{
          city = data;
        }
        break;
        
      default:
        city = '3';
        break;
    }
  } else {
    city = '3';
  }
  
  delay(500);  // Adjust the delay as per your requirements
}


void cameraON(){
  if (arduinoSerial.available()) {
    arduinoSerial.write("1");
    Serial.println("Sent");
    delay(1000);
  }else{
    Serial.println("Serial not available");
    Serial.println("Retrying....");
    delay(500);
    cameraON();
  }
}