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

#include "auxiliaryinputprocess.h"

void AuxiliaryInputProcess::configure(byte aPinNumber, AuxiliaryInput* aAuxiliaryInput)
{
  pin = aPinNumber;
  output = aAuxiliaryInput;
  resume();
}

bool AuxiliaryInputProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  output->reading = analogRead(pin);
  hibernate(250);
}

