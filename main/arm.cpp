#include "arm.h"

// Servo connections
Servo servoDown; // Bottom servo
Servo servoUp;   // Top servo
Servo grip;


#define fix 110
#define rel 75
#define bottom 85
#define rightBot 100
#define up 160
#define midLoc 135
#define rightLoc 40

void setupArm()
{
  // Set servo to initial position
  Serial.println("Arm is setting up....");
  servoDown.attach(8);
  servoDown.write(midLoc);
  servoUp.attach(7);
  servoUp.write(up);
  grip.attach(6);
  grip.write(rel);
  Serial.println("Arm is setup completed.");
}

void grab()
{
  Serial.println("Grabbing item...");
  // grip.write(fix);
   for (int i = rel; i < fix; i++, grip.write(i), delay(20));
}

void liftBox()
{
  Serial.println("Lifting...");
  for (int i = bottom; i < up; i++, servoUp.write(i), delay(20));
}

void liftBoxRight()
{
  Serial.println("Lifting...");
  for (int i = rightBot; i < up; i++, servoUp.write(i), delay(20));
}

void putDown()
{
  Serial.println("Putting down...");
  for (int i = up; i > bottom; i--, servoUp.write(i), delay(20));
  delay(1000);
}

void putDownRight()
{
  Serial.println("Putting down...");
  for (int i = up; i > rightBot; i--, servoUp.write(i), delay(20));
  delay(1000);
}

void release()
{
  Serial.println("Realesing and going up....");
  grip.write(rel);
  delay(500);
}

void turnLeft()
{
  Serial.println("Turning to left....");
  for (int i = midLoc; i > rightLoc; i--, servoDown.write(i), delay(20));
  delay(500);
}

void turnMid()
{
  Serial.println("Turning to middle position....");
  for (int i = rightLoc; i < midLoc; i++, servoDown.write(i), delay(20));
  delay(500);
}