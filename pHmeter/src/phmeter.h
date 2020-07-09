/*
  # This sample code is used to test the pH meter V1.1.
  # Editor : YouYou
  # Ver    : 1.1
  # DAT    : 2014.06.23
  # Product: analog pH meter V1.1
  # SKU    : SEN0161
*/
#ifndef _PHMETER_H_
#define _PHMETER_H_

#include "phmeter.h"
#include <Arduino.h>

#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
class Phmeter
{
private:
    int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
    int pHArrayIndex = 0;
    float Offset = -4.44;           //deviation compensate
    double avergearray(int* arr, int number);
    float pHValue, voltage;
    uint8_t analogPin;
public:
    Phmeter(uint8_t pin);
    float getPH();
    float getVoltage();
    void calibrate(float cal);
    ~Phmeter();
};

#endif