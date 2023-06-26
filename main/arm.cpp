#include "arm.h"

// Servo connections
Servo servoDown; // Bottom servo
Servo servoUp;   // Top servo
Servo grip;

void setupArm()
{
  // Set servo to initial position
  Serial.println("Arm is setting up....");
  servoDown.attach(4);
  servoDown.write(45);
  // servoDown.detach();
  servoUp.attach(5);
  servoUp.write(180);
  grip.attach(6);
  grip.write(10);
  Serial.println("Arm is setup completed.");
}

void grab()
{
  for (int i = 180; i > 85; i--, servoUp.write(i), delay(20))
    ;
  delay(700);
  grip.write(70);
  servoDown.write(45);
}

void liftBox()
{
  for (int i = 85; i < 180; i++, servoUp.write(i), delay(20))
    ;
  grip.write(70);
  servoDown.write(45);
}

void putDown()
{
  Serial.println("Putting down...");
  for (int i = 180; i > 85; i--, servoUp.write(i), delay(20))
    ;
  delay(500);
  grip.write(70);
  servoDown.write(45);
  delay(1000);
}

void releaseUp()
{
  Serial.println("Realesing and going up....");
  grip.write(20);
  for (int i = 85; i < 180; i++, servoUp.write(i), delay(20))
    ;
  servoDown.write(45);
  delay(500);
}

void turnLeft()
{
  Serial.println("Turning to left....");
  servoUp.write(180);
  grip.write(70);
  for (int i = 45; i < 140; i++, servoDown.write(i), delay(20))
    ;
  delay(500);
}

void turnMid()
{
  Serial.println("Turning to middle position....");
  servoUp.write(180);
  grip.write(20);
  for (int i = 140; i > 44; i--, servoDown.write(i), delay(20))
    ;
  delay(500);
}

void testGrip(int position)
{
  grip.write(position);
}