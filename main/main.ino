#include "measure.h"
#include "move.h"
#include "arm.h"
#include "rfid.h"
#include "gyroscope.h"
#include "dataTransfer.h"

#define minDis 9
#define maxDis 10

int distance = 0;
int direction = -99;
int count = 3;  //number of box
int val;
char city = "";
bool boxfound = false;  //status about box found or not
bool grabBox = false; //status about the box grabed or not
bool addressFound = false;  //status about correct address found or not

void setup() {
  Serial.begin(9600);
  setupMeasure();
  setupWheels();
  setupArm();
  setupGyroscope();
  setupRfid();
  Serial.println("Waiting....");
  delay(3000);
}

void loop() {
  distance = measure();
  if (count < 0){
    Serial.println("All done.");
    for (;;);
  }
  if (!boxfound){
    Serial.println("Box not detect.");
    if (minDis <= distance && distance < maxDis){
      Serial.println("Box detected.");

      boxfound = true;
      count -= 1; //grab one
      cameraON();

      while(1){
        city = getQRData();
        if (city != ""){
          Serial.println(city);
          break;
        }
      }
      //call to python server and turn on cam server
      release();
      putDown();
      grab();
      liftBox();
      grabBox = true;
    }else if(distance < minDis){
      Serial.println("Too close to box");
      while (distance < minDis){
        backward();
        direction = getGyroscope();
        if (direction == 1){
          moveRight();
          delay(200);
        }else if(direction == -1){
          moveLeft();
          delay(200);
        }
        else if(direction == 0){
          backward();
        }
        backward();
        distance = measure();
      }
      stop();
      if (minDis <= distance < maxDis){
        Serial.println("Box detected.");

        boxfound = true;
        count -= 1; //grab one
        cameraON();

        while(1){
          city = getQRData();
          if (city != ""){
            Serial.println(city);
            break;
          }
        }
        release();
        putDown();
        grab();
        liftBox();
        grabBox = true;
      }
    }else{
      Serial.println("Too far from the box.");
      while (distance > maxDis){
        forward();
        distance = measure();
      }
      stop();
      if (minDis <= distance < maxDis){
        Serial.println("Box detected.");

        boxfound = true;
        count -= 1; //grab one
        cameraON();

        while(1){
          city = getQRData();
          if (city != ""){
            Serial.println(city);
            break;
          }
        }
        release();
        putDown();
        grab();
        liftBox();
        grabBox = true;
      }
    }
  }else{
    if (grabBox){
      backward();
      addressFound = readRfid("Colombo");
      // addressFound = readRfid(city);
      delay(500);
      Serial.print("addressFound: ");
      Serial.println(addressFound);
      delay(500);
      if (addressFound && boxfound){
        stop();
        turnLeft();
        putDown();
        release();
        liftBox();
        turnMid();
        boxfound = false;
        addressFound = false;
        grabBox = false;
        Serial.println("One Work Done....");
        delay(4000);
      }
      // getDecision();
      // Serial.println("Box droped to correct location");
    }
    // boxfound = false;
  }
}