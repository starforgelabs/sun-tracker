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

#include "seekerprocess.h"

int sgn(int value)
{
  if(value < 0)
    return -1;
  else if (value > 0)
    return +1;
  else
    return 0;
}

void SeekerProcess::configure(SensorReadings* aSensorReadings, MotorControl* aBaseMotorControl, MotorControl* aSensorMotorControl)
{
  sensors = aSensorReadings;
  baseMotor = aBaseMotorControl;
  sensorMotor = aSensorMotorControl;
  
  baseRailCount = 0;
  
  hibernate(3000);
  resume();
}

bool SeekerProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  getDeltas();
  
  // xxxDelta is how much delta to move a motor.
  int baseDelta = 0;
  int sensorDelta = 0;

  // xxxPairName is the sensor pair to use for decision making.   
  int basePairName   = abs(Deltas[brDelta]) > abs(Deltas[ygDelta]) ? brDelta : ygDelta;
  int sensorPairName = abs(Deltas[ybDelta]) > abs(Deltas[grDelta]) ? ybDelta : grDelta;

  if(abs(Deltas[basePairName]) > 5)
    baseDelta = sgn(Deltas[basePairName]);

  if(abs(Deltas[sensorPairName]) > 3)
    sensorDelta = -sgn(Deltas[sensorPairName]);

  // Invert base motor direction if the sensor board is turned around.    
  if(sensorMotor->getTarget() < 0)
    baseDelta = -baseDelta;
    
  baseMotor->moveDelta(baseDelta);
  sensorMotor->moveDelta(sensorDelta);
  
  if(baseMotor->getTarget() == baseMotor->Max)
  {
     if(baseDelta > 0) 
       baseRailCount++;
  }
  else if(baseMotor->getTarget() == baseMotor->Min)
  {
     if(baseDelta < 0) 
       baseRailCount++;
  }
  else
    baseRailCount = 0;
    
  if(baseRailCount > 2000) 
  {
    baseMotor->home();
    sensorMotor->home();
    hibernate(1000);
    return true;
  }
    
  hibernate(1);
  return true;
}

void SeekerProcess::getDeltas()
{
  Deltas[ygDelta] = sensors->yellow.normalized - sensors->green.normalized;
  Deltas[ybDelta] = sensors->yellow.normalized - sensors->blue.normalized;
  Deltas[yrDelta] = sensors->yellow.normalized - sensors->red.normalized;
  Deltas[gbDelta] = sensors->green.normalized  - sensors->blue.normalized;
  Deltas[grDelta] = sensors->green.normalized  - sensors->red.normalized;
  Deltas[brDelta] = sensors->blue.normalized   - sensors->red.normalized;
}


