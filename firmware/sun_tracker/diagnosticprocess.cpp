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

#include "diagnosticprocess.h"

boolean DiagnosticProcess::clearDisplay()
{
  if(!isClearing)
  {
    Serial.write(12);
    hibernate(5);
    isClearing = true;
  }
  else
    isClearing = false;
    
  return isClearing;
}

void DiagnosticProcess::configure(AuxiliaryInput* aAuxiliaryInput, SensorReadings* aSensorReadings)
{
  currentProgram = dpInit;
  lastDisplayProgram = dpInit;
  isClearing = false;
  
  input = aAuxiliaryInput;
  sensors = aSensorReadings;
  
  // The LCD requires 100 mS of initialization time.
  Serial.write(12);
  hibernate(100);
  resume();
}

void DiagnosticProcess::displayAppInfo()
{
  if(lastDisplayProgram != currentProgram && clearDisplay()) return;
  
  Serial.print("Sun Tracker\n\r");
  lastDisplayProgram = currentProgram;
  currentProgram = dpIdle;
  hibernate(3000);
}

void DiagnosticProcess::displayBlueInfo()
{
  if(lastDisplayProgram != currentProgram && clearDisplay()) return;
  
  writeColourInfo("Blue", &sensors->blue);
  
  lastDisplayProgram = currentProgram;
  currentProgram = dpIdle;
  hibernate(100);
}

void DiagnosticProcess::displayGreenInfo()
{
  if(lastDisplayProgram != currentProgram && clearDisplay()) return;

  writeColourInfo("Green", &sensors->green);
  
  lastDisplayProgram = currentProgram;
  currentProgram = dpIdle;
  hibernate(100);
}

void DiagnosticProcess::displayRedInfo()
{
  if(lastDisplayProgram != currentProgram && clearDisplay()) return;

  writeColourInfo("Red", &sensors->red);
  
  lastDisplayProgram = currentProgram;
  currentProgram = dpIdle;
  hibernate(100);
}

void DiagnosticProcess::displayYellowInfo()
{
  if(lastDisplayProgram != currentProgram && clearDisplay()) return;

  writeColourInfo("Yellow", &sensors->yellow);
  
  lastDisplayProgram = currentProgram;
  currentProgram = dpIdle;
  hibernate(100);
}

bool DiagnosticProcess::execute()
{
  if(!SCMProcess::execute()) return false;
  
  switch(currentProgram)
  {
    case dpInit:       initializeDisplay(); return true;
    case dpAppInfo:    displayAppInfo(); return true;
    case dpBlueInfo:   displayBlueInfo(); return true;
    case dpRedInfo:    displayRedInfo(); return true;
    case dpYellowInfo: displayYellowInfo(); return true;
    case dpGreenInfo:  displayGreenInfo(); return true;
    default:           idle(); return true;
  }
}

void DiagnosticProcess::idle()
{
  int program = map(input->reading, 0, 1023, 0, 5);
  switch(program)
  {
    case 0: currentProgram = dpBlueInfo; break;
    case 1: currentProgram = dpRedInfo; break;
    case 2: currentProgram = dpYellowInfo; break;
    case 3: currentProgram = dpGreenInfo; break;
    default: currentProgram = dpGreenInfo; break;
  }
}

void DiagnosticProcess::initializeDisplay()
{
  Serial.print("\x16\xD2\xDA\xE5\xD3\xE3\xE5\xD4\xE1");
  // Next step in the state machine.
  currentProgram = dpAppInfo;
}

void DiagnosticProcess::writeColourInfo(char* aName, SensorReading* aReading)
{
  Serial.write(0x80); // Move to upper line, 1st character
  Serial.print(aName);
  Serial.write(0x87); // Move to upper line, 8th characer
  Serial.print("raw=    "); 
  Serial.write(0x8B); // Move to upper line, 12th characer
  Serial.print(aReading->raw);
  Serial.print("\rNormalized=    ");
  Serial.write(0x9F); // Move to lower line, 12th characer
  Serial.print(aReading->normalized);
}


