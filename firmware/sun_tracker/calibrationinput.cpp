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
#include "calibrationinput.h"

void CalibrationInput::configure(MotorControl* aControl)
{
  controller = aControl;
  resume();
}

bool CalibrationInput::execute()
{
  if(!SCMProcess::execute()) return false;
  
  int reading = analogRead(AuxillaryInputPin);
  int servoValue = map(reading, 0, 1023, MotorControl::Min, MotorControl::Max);
  controller->setTarget(servoValue);
}

