#ifndef DATATRANSFER_H
#define DATATRANSFER_H
#include <Arduino.h>
#include <SoftwareSerial.h>

void setupDataTransfer();
void getQRData(char &city);
void cameraON();


#endif