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

#ifndef AUXILIARY_INPUT_PROCESS_H
#define AUXILIARY_INPUT_PROCESS_H

#include <SCMProcess.h>

struct AuxiliaryInput {
  int reading;
};

class AuxiliaryInputProcess : public SCMProcess
{
  public:
  void configure(byte aPinNumber, AuxiliaryInput* aAuxiliaryInput);
  virtual bool execute();  
  
  private:
  byte pin;
  AuxiliaryInput* output;
};

#endif//AUXILIARY_INPUT_PROCESS_H

