#include "move.h"
#include <Servo.h>
// Motor A connections
int in1 = A3;
int in2 = A2;

// Motor B connections
int in3 = A1;
int in4 = A0;

void setupWheels(){
  Serial.println("Wheels setup starting...");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.println("Wheels setup completed.");
}

void forward(){
  Serial.println("Forward...");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(){
  Serial.println("Backward...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop(){
  Serial.println("Stoping...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}