#include "measure.h"

int trigPin = 2;
int echoPin = 3;

void setupMeasure(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
int measure(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = (duration/2) / 29.1;    //obtain distance
  Serial.println(distance);
  delay(1000);
  if (distance > 0){
    return distance;
  }else{
    measure();
  }
}