#ifndef GYROSCOPE_H
#define GYROSCOPE_H
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

void setupGyroscope();
float getGyroscope();
void getAvg();
void getDecision();


#endif