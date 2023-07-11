#ifndef RFID_H
#define RFID_H
#include <Arduino.h>
#include <SPI.h>
#include <RFID.h>

void setupRfid();
bool readRfid(char *address);


#endif