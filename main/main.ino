#include "measure.h"
#include "move.h"
#include "arm.h"
#include "rfid.h"
// #include "gyroscope.h"

int distance = 0;
int val;
bool boxfound = false;  //status about box found or not
bool grabBox = false; //status about the box grabed or not
bool addressFound = false;  //status about correct address found or not

void setup() {
  Serial.begin(9600);
  setupMeasure();
  setupWheels();
  setupArm();
  // setupGyroscope();
  setupRfid();
  Serial.println("Waiting....");
  delay(3000);
}

void loop() {
  
  distance = measure();

  if (!boxfound){
    Serial.println("Box not detect.");
    if (11 <= distance && distance < 18){
      Serial.println("Box detected.");
      boxfound = true;
      grab();
      liftBox();
      grabBox = true;
    }else if(distance < 11){
      Serial.println("Too close to box");
      while (distance < 10){
        backward();
        distance = measure();
      }
      stop();
      if (11 <= distance < 18){
        Serial.println("Box detected.");
        boxfound = true;
        grab();
        liftBox();
        grabBox = true;
      }
    }else{
      Serial.println("Too far from the box.");
      while (distance > 18){
        forward();
        distance = measure();
      }
      stop();
      if (11 <= distance < 18){
        Serial.println("Box detected.");
        boxfound = true;
        grab();
        liftBox();
        grabBox = true;
      }
    }
  }else{
    if (grabBox){
      backward();
      addressFound = readRfid("Colombo");
      Serial.println(addressFound);
      if (addressFound){
        stop();
        putDown();
        releaseUp();
      }
      // getDecision();
      Serial.println("Box droped to correct location");
    }
    // boxfound = false;
  }
}