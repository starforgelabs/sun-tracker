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

bool SeekerProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  int brDelta = sensors->blue.normalized - sensors->red.normalized;
  int ygDelta = sensors->yellow.normalized - sensors->green.normalized;
  int ybDelta = sensors->yellow.normalized - sensors->blue.normalized;
  
  if(brDelta < -5)
  {
//    if(abs(baseMotor->getTarget()) == baseMotor->Max)
//    {
//      baseMotor->moveDelta(900);
//      sensorMotor->home();
//    }
//    else
      baseMotor->moveDelta(-1);
  }
  else if(brDelta > 5) 
  {
//    if(abs(baseMotor->getTarget()) == baseMotor->Max)
//    {
//      baseMotor->moveDelta(-900);
//      sensorMotor->home();
//    }
//    else
    baseMotor->moveDelta(+1);
  }
//  else if(ygDelta < -10)
//    movePositive();
//  else if(ygDelta > 10)
//    moveNegative();

  if(ybDelta < -3)
    sensorMotor->moveDelta(+1);
  else if(ybDelta > 3) 
    sensorMotor->moveDelta(-1);
    
  hibernate(1);
}

void SeekerProcess::configure(SensorReadings* aSensorReadings, MotorControl* aBaseMotorControl, MotorControl* aSensorMotorControl)
{
  sensors = aSensorReadings;
  baseMotor = aBaseMotorControl;
  sensorMotor = aSensorMotorControl;
  
  hibernate(3000);
  resume();
}

