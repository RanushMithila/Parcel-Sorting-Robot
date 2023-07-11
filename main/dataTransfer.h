#ifndef DATATRANSFER_H
#define DATATRANSFER_H
#include <Arduino.h>
#include <SoftwareSerial.h>

void setupDataTransfer();
char *getQRData();
void cameraON();


#endif