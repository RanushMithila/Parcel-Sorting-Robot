#include "arm.h"

// Servo connections
Servo servoDown; // Bottom servo
Servo servoUp;   // Top servo
Servo grip;


#define fix 80
#define rel 20

void setupArm()
{
  // Set servo to initial position
  Serial.println("Arm is setting up....");
  servoDown.attach(8);
  servoDown.write(40);
  servoUp.attach(7);
  servoUp.write(100);
  grip.attach(6);
  grip.write(10);
  Serial.println("Arm is setup completed.");
}

void grab()
{
  Serial.println("Grabbing item...");
  // grip.write(fix);
   for (int i = 85; i < 180; i++, grip.write(i), delay(20));
}

void liftBox()
{
  Serial.println("Lifting...");
  for (int i = 20; i < 100; i++, servoUp.write(i), delay(20));
}

void putDown()
{
  Serial.println("Putting down...");
  for (int i = 100; i > 20; i--, servoUp.write(i), delay(20));
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
  for (int i = 40; i < 140; i++, servoDown.write(i), delay(20));
  delay(500);
}

void turnMid()
{
  Serial.println("Turning to middle position....");
  for (int i = 140; i > 39; i--, servoDown.write(i), delay(20));
  delay(500);
}

void testGrip(int position)
{
  servoDown.write(position);
}