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

#ifndef DIAGNOSTIC_PROCESS_H
#define DIAGNOSTIC_PROCESS_H

#include <SCMProcess.h>
#include "auxiliaryinputprocess.h"
#include "sensorprocess.h"

class DiagnosticProcess : public SCMProcess
{
  public:
  void configure(AuxiliaryInput* aAuxiliaryInput, SensorReadings* aSensorReadings);
  virtual bool execute();
  
  private:
  AuxiliaryInput* input;
  char lastProgram;
  char* pc;
  SensorReadings* sensors;
  
  void writeColourInfo(char* aName, SensorReading* aReading);
};

#endif//DIAGNOSTIC_PROCESS_H
