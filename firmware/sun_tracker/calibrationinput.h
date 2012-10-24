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

#ifndef CALIBRATION_INPUT_H
#define CALIBRATION_INPUT_H

#include <SCMProcess.h>
#include "MotorControl.h"

class CalibrationInput : public SCMProcess
{
  public:
  void configure(MotorControl* aControl);
  virtual bool execute();  
  
  private:
  MotorControl* controller;
};

#endif//CALIBRATION_INPUT_H

