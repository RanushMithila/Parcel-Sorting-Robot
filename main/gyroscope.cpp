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

float getGyroscope(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("X: ");
  Serial.println(a.acceleration.x);

  delay(500);
  return a.acceleration.x;
}

void getAvg(){
  Serial.println("function called");
  int count = 4;
  float tot = 0.0;
  while (count >= 0){
    tot += getGyroscope();
    count--;
  }
  Serial.println(tot);
  avg = tot/5;
}

void getDecision(){
  // Serial.println("function called");
  getAvg();
  // Serial.println("Calculating avg");
  float diff = abs(getGyroscope() - avg);
  if (diff > 0.15){
    Serial.println("Turn");
  }else{
    Serial.println("Don't turn");
  }
}
