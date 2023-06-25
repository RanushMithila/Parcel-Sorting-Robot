#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(3, 2);  // RX, TX pins connected to ESP32

void setup() {
  Serial.begin(115200);  // Serial monitor for debugging
  arduinoSerial.begin(9600);  // Serial communication with ESP32
}

void loop() {
  // Serial.print("Test");
  if (arduinoSerial.available()) {
    String receivedData;
    while (arduinoSerial.available()) {
        receivedData += (char)arduinoSerial.read();  // Read data from the Arduino Uno
    }
    // int data = receivedData.toInt();  // Convert the received string to an integer
    Serial.print("Received data: ");
    Serial.println(receivedData);
  }
  delay(500);
  // Add any additional code for the main loop
}
