#include "gyroscope.h"

Adafruit_MPU6050 mpu;
float avg = 0.0;

void setupGyroscope(){
    while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  delay(100);
}

int getGyroscope(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (a.acceleration.x >= 1) {
    Serial.println(" - Turning Right");
    return 1;
  } else if (a.acceleration.x <= -1) {
    Serial.println(" - Turning Left");
    return -1;
  } else {
    Serial.println(" - Going Straight");
    return 0;
  }
}