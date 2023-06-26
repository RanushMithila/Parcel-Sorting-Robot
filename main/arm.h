#ifndef ARM_H
#define ARM_H
#include <Arduino.h>
#include <Servo.h>

void setupArm();
void testGrip(int position);
void grab();
void liftBox();
void putDown();
void releaseUp();
void turnLeft();
// void releaseLeft();
// void releaseRight();

#endif