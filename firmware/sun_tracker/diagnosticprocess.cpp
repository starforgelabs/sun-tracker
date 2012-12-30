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

void DiagnosticProcess::configure(AuxiliaryInput* aAuxiliaryInput, SensorReadings* aSensorReadings)
{
  input = aAuxiliaryInput;
  pc = "PdDR";
  sensors = aSensorReadings;
  
  resume();
}

bool DiagnosticProcess::execute()
{
  if(!SCMProcess::execute()) return false;

  // Assign new program if execution completed.  
  if(pc == NULL || *pc == 0) pc = "R";
  
  switch(*pc++)
  {
    // Clear
    case 'C': 
      // The LCD requires 5 mS of reset time.
      Serial.write(12);
      hibernate(5);
      break;
      
    // Delay
    case 'D': 
      hibernate(3000);
      break;
      
    // First-time initialization
    case 'I': 
      // Documentation for the serial display states that to 
      // initialize the display, the transmit pin has to be 
      // pulled high, then wait for 100 mS.
      digitalWrite(1, HIGH);
      hibernate(100);
      break;
      
    // Play start-up music
    case 'P':
      Serial.print("\x16\xD2\xDA\xE5\xD3\xE3\xE5\xD4\xE1");
      break;
      
    // Normal run state.
    case 'R':
      switch(map(input->reading, 0, 1023, 0, 5))
      {
        case 0:  pc = "Cb"; if(lastProgram=='b') pc++; lastProgram = 'b'; break;
        case 1:  pc = "Cr"; if(lastProgram=='r') pc++; lastProgram = 'r'; break;
        case 2:  pc = "Cy"; if(lastProgram=='y') pc++; lastProgram = 'y'; break;
        case 3:  pc = "Cg"; if(lastProgram=='g') pc++; lastProgram = 'g'; break;
        default: pc = "Cd"; if(lastProgram=='d') pc++; lastProgram = 'd'; break;
      }
      break;
      
    // Display Blue   Information
    case 'b':
      writeColourInfo("Blue", &sensors->blue);
      hibernate(100);
      break;
      
    // Display program information
    case 'd': 
      Serial.print("Sun Tracker\n\r");
      break;
      
    // Display Green  Information
    case 'g':
      writeColourInfo("Green", &sensors->green);
      hibernate(100);
      break;
      
    // Display Red    Information
    case 'r':
      writeColourInfo("Red", &sensors->red);
      hibernate(100);
      break;
      
    // Display Yellow Information
    case 'y':
      writeColourInfo("Yellow", &sensors->yellow);
      hibernate(100);
      break;
  }
  
  return true;
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

