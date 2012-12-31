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

#ifndef SEEKER_PROCESS_H
#define SEEKER_PROCESS_H

#include <SCMProcess.h> 
#include "sensorprocess.h"
#include "motorcontrol.h"

enum SeekerDeltas {ygDelta, ybDelta, yrDelta, gbDelta,  grDelta, brDelta};

class SeekerProcess : public SCMProcess
{
  public:
  virtual bool execute();
  void configure(SensorReadings* aSensorReadings, MotorControl* aBaseMotorControl, MotorControl* aServoMotorControl);
  
  private:
  SensorReadings* sensors;
  MotorControl* baseMotor;
  MotorControl* sensorMotor;
  int Deltas[6];
  int baseRailCount;
  
  void getDeltas();
};

#endif//SEEKER_PROCESS_H

