#include "dataTransfer.h"

SoftwareSerial arduinoSerial(7, 8);  // RX, TX pins connected to ESP32

void setupDataTransfer(){
  Serial.begin(115200);  // Serial monitor for debugging
  arduinoSerial.begin(9600);  // Serial communication with ESP32
}


void getData(){
  if (arduinoSerial.available()) {
    String receivedData;
    while (arduinoSerial.available()) {
        receivedData += (char)arduinoSerial.read();  // Read data from the Esp32
    }
    // int data = receivedData.toInt();  // Convert the received string to an integer
    Serial.print("Received data: ");
    Serial.println(receivedData);
  }
  // return receivedData;
  delay(500);
}

void cameraON(){
  arduinoSerial.write(1);
  Serial.println("Sent");
}