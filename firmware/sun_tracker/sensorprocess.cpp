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

#include "suntracker.h"
#include "sensorprocess.h"

void SensorProcess::configure(DataNormalizer* aSensor, SensorReadings* aReadings)
{
  sensors = aSensor;
  readings = aReadings;

  blueIndex = sensors->IndexOf(BlueSensorPin);
  redIndex = sensors->IndexOf(RedSensorPin);
  yellowIndex = sensors->IndexOf(YellowSensorPin);
  greenIndex = sensors->IndexOf(GreenSensorPin);
  
  resume();
}

bool SensorProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  // Tell the scheduler we'll want to sleep 1mS from this point of time. 
  // While the clock is ticking, we'll actually be processing sensors.
  // What this does is it makes the delay at least 1mS rather than 
  // 1mS + the amount of processing time. 
  hibernate(10); 
  if(!sensors->ReadAndNormalize())
  {
    int errorValue = -(int)sensors->StatusCode();
    readings->blue.raw          = errorValue;
    readings->blue.normalized   = errorValue;
    readings->red.raw           = errorValue;
    readings->red.normalized    = errorValue;
    readings->yellow.raw        = errorValue;
    readings->yellow.normalized = errorValue;
    readings->green.raw         = errorValue;
    readings->green.normalized  = errorValue;
    return true;
  }

  // Cache readings
  readings->blue.raw          = sensors->Values[blueIndex];
  readings->blue.normalized   = sensors->Normalized[blueIndex];
  readings->red.raw           = sensors->Values[redIndex];
  readings->red.normalized    = sensors->Normalized[redIndex];
  readings->yellow.raw        = sensors->Values[yellowIndex];
  readings->yellow.normalized = sensors->Normalized[yellowIndex];
  readings->green.raw         = sensors->Values[greenIndex];
  readings->green.normalized  = sensors->Normalized[greenIndex];
  return true;
}

