#include "measure.h"
#include "move.h"
#include "arm.h"
#include "rfid.h"
#include "dataTransfer.h"

#define minDis 9
#define maxDis 10

int distance = 0;
int count = 3;  //number of box
int val;
char city = NULL;
bool boxfound = false;  //status about box found or not
bool grabBox = false; //status about the box grabed or not
bool addressFound = false;  //status about correct address found or not

void setup() {
  Serial.begin(9600);
  setupMeasure();
  setupWheels();
  setupArm();
  setupRfid();
  setupDataTransfer();
  Serial.println("Waiting....");
  delay(3000);
}

void loop() {
  distance = measure();
  if (count <= 0){
    Serial.println("All done.");
    for (;;);
  }
  if (!boxfound){
    Serial.println("Box not detect.");
    if (minDis <= distance && distance < maxDis){
      Serial.println("Box detected.");

      boxfound = true;
      while(1){
        cameraON();
        getQRData(city);
        Serial.print("city: ");
        Serial.println(city);
        if (city == '9' || city == '8' || city == '7' || city == '6'){
          Serial.println(city);
          break;
        }
        Serial.println("Not correct");
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
        distance = measure();
      }
      stop();
      if (minDis <= distance < maxDis){
        Serial.println("Box detected.");

        boxfound = true;
        while(1){
          cameraON();
          getQRData(city);
          Serial.print("city: ");
        Serial.println(city);
          if (city == '9' || city == '8' || city == '7' || city == '6'){
            Serial.println(city);
            break;
          }
          Serial.println("Not correct");
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
        while(1){
          cameraON();
          getQRData(city);
          Serial.print("city: ");
        Serial.println(city);
          if (city == '9' || city == '8' || city == '7' || city == '6'){
            Serial.println(city);
            break;
          }
          Serial.println("Not correct");
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
      Serial.print("city: ");
      Serial.println(city);
      backward();
      // addressFound = readRfid("Colombo");
      addressFound = readRfid(city);
      delay(500);
      Serial.print("addressFound: ");
      Serial.println(addressFound);
      delay(500);
      if (addressFound && boxfound){
        stop();
        turnLeft();
        putDownRight();
        release();
        liftBoxRight();
        turnMid();
        boxfound = false;
        addressFound = false;
        grabBox = false;
        Serial.println("One Work Done....");
        count -= 1; //drop one
        Serial.print("City: ");
        Serial.println(city);
        delay(4000);
      }
      // getDecision();
      // Serial.println("Box droped to correct location");
    }
    // boxfound = false;
  }
}