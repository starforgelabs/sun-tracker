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

#include "motorprocess.h"

void MotorProcess::configure(byte aPinNumber, MotorControl* aController, int aLowMicroseconds, int aMidpointMicroseconds, int aHighMicroseconds)
{
  pin = aPinNumber;
  controller = aController;
  lowUS = aLowMicroseconds;
  midpointUS = aMidpointMicroseconds;
  highUS = aHighMicroseconds;
  
  servo.attach(pin);
  resume();
}

bool MotorProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  int uS = targetAsMicroseconds();
  servo.writeMicroseconds(uS);
  hibernate(1);
  return true;
}

int MotorProcess::targetAsMicroseconds()
{
  int target = controller->getTarget();
  if(target == 0)
    return midpointUS;
  else if(target < 0)
    return map(target, MotorControl::Min, 0, lowUS, midpointUS);
  else
    return map(target, 0, MotorControl::Max, midpointUS, highUS);
}


