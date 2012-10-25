/*
* Copyright 2012 James Knowles. 
*
* This work is licensed under a Creative Commons
* Attribution-ShareAlike 3.0 Unported License.
*
* https://creativecommons.org/licenses/by-sa/3.0/
*
* This code is strictly "as is". Use at your own risk.
*
*/

#ifndef SENSOR_PROCESS_H
#define SENSOR_PROCESS_H

#include "Arduino.h"
#include <SCMProcess.h> 
#include <DataNormalizer.h>

struct SensorReading 
{
  SensorReading() : raw(0), normalized(0) {}
  int raw;
  int normalized;
};

struct SensorReadings
{
  SensorReading blue;
  SensorReading red;
  SensorReading yellow;
  SensorReading green;
};

class SensorProcess : public SCMProcess
{
  public:  
  void configure(DataNormalizer* aSensor, SensorReadings* aReadings);
  virtual bool execute();
  
  private:
  DataNormalizer* sensors;
  SensorReadings* readings;
  
  byte blueIndex;
  byte redIndex;
  byte yellowIndex;
  byte greenIndex;
};

#endif//SENSOR_PROCESS_H

