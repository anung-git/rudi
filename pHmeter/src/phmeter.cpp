#include "phmeter.h"

void Phmeter::calibrate(float cal){
    this->Offset=cal; 
}

float Phmeter::getPH(){

    this->pHValue = 3.5 * this->getVoltage() + this->Offset;
    return this->pHValue ;
}

float Phmeter::getVoltage(){
    this->pHArray[pHArrayIndex++] = analogRead(analogPin);
    if (this->pHArrayIndex == ArrayLenth) this->pHArrayIndex = 0;
    this->voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024 + 0.05;
    return this->voltage;
}

Phmeter::Phmeter(uint8_t pin){
    this->analogPin=pin;
}

Phmeter::~Phmeter(){
}


double Phmeter::avergearray(int* arr, int number){
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0)
  {
    // Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) //less than 5, calculated directly statistics
  {
    for (i = 0; i < number; i++)
    {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  }
  else
  {
    if (arr[0] < arr[1])
    {
      min = arr[0]; max = arr[1];
    }
    else
    {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++)
    {
      if (arr[i] < min)
      {
        amount += min;      //arr<min
        min = arr[i];
      }
      else
      {
        if (arr[i] > max)
        {
          amount += max;  //arr>max
          max = arr[i];
        }
        else
        {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}


