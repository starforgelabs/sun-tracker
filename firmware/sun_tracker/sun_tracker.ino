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

#include <Servo.h>
#include <SCMScheduler.h>
#include <SCMProcess.h>
#include "suntracker.h"
#include "motor.h"
#include "calibrationinput.h"

MotorControl baseControl;
MotorControl sensorControl;

MotorProcess baseMotorProcess;
MotorProcess sensorMotorProcess;
CalibrationInput calibrationProcess;

#define PROCESS_COUNT 3
SCMProcess* processList[PROCESS_COUNT];
SCMScheduler scheduler(processList, PROCESS_COUNT);

void setup()
{
  processList[0] = &baseMotorProcess;
  processList[1] = &sensorMotorProcess;
  processList[2] = &calibrationProcess;
  
  calibrationProcess.configure(&sensorControl);
  baseMotorProcess.configure(LowerServoPin, &baseControl, BaseServoLowBound, BaseServoMidpoint, BaseServoUpperBound);
  sensorMotorProcess.configure(UpperServoPin, &sensorControl, SensorServoLowBound, SensorServoMidpoint, SensorServoUpperBound);
  
  Serial.begin(9600);
}

void loop()
{
  scheduler.run();
}



