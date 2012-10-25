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

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"

//
// This is a messanger object that stands between a motor process, 
// which actually controls a motor, and other processes that want to
// tell the motors what they should do. 
//
// Other processes talk to this virtual "motor control" object without 
// having to be concerned about the details of talking to the motor, 
// jitter control, etc. etc. etc. 
//
class MotorControl
{
  // Motor control values are abstracted between 
  // -90.0 degrees to +90.0 degress, in tenths of a degree. 
  public: 
  static const int Max =  900;
  static const int Min = -900;
  
  public:
  MotorControl() : target(0) {}
    
  void home() { target = 0; }
  
  int getTarget() { return target; }
  void setTarget(int aValue) { target = constrain(aValue, Min, Max); }
    
  private:
  int target;
};

#endif//MOTOR_CONTROL_H

