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

#ifndef MOTOR_PROCESS_H
#define MOTOR_PROCESS_H

#include <SCMProcess.h>
#include "motorcontrol.h"
#include <Servo.h>

//
// This class actually controls a motor (servo). 
//
// It reads the desired virtual position from the MotorControl object.
// If there are physical contraints, jitter problems, etc. they will
// be handled by this class, isolating the rest of the syste from the 
// physical motors.
//
class MotorProcess : public SCMProcess
{
  public:
  void configure(byte aPinNumber, MotorControl* aController, int aLowMicroseconds, int aMidpointMicroseconds, int aHighMicroseconds);
  virtual bool execute();
  
  // Motor information
  private:
  byte pin;
  MotorControl* controller;
  Servo servo;
  int lowUS;      // low range pulse width (μS) 
  int midpointUS; // centre range pulse width (μS) 
  int highUS;     // high range pulse width (μS) 
  
  private:
  int targetAsMicroseconds();
};

#endif//MOTOR_PROCESS_H


