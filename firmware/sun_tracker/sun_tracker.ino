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

#include <BaseAnalogRead.h>
#include <BufferedAnalogRead.h> 
#include <AveragingAnalogRead.h>
#include <DataNormalizer.h>
#include <Servo.h>
#include <SCMScheduler.h>
#include <SCMProcess.h>

#include "suntracker.h"
#include "calibrationdata.h"

#include "auxiliaryinputprocess.h"
#include "diagnosticprocess.h"
#include "motorprocess.h"
#include "sensorprocess.h"

////////////////////////////////////////////////////////////////////////////////
//
// Sensors
//
////////////////////////////////////////////////////////////////////////////////

BaseAnalogRead* sources[SensorCount] =
{
  new AveragingAnalogRead(BlueSensorPin),
  new AveragingAnalogRead(RedSensorPin),
  new AveragingAnalogRead(YellowSensorPin),
  new AveragingAnalogRead(GreenSensorPin)
};
const int* CalibrationVectors[SensorCount];
DataNormalizer sensors;

////////////////////////////////////////////////////////////////////////////////
//
// Very primitive inter-process communication messages.
//
// The software for the sun tracker is simple enough that these are fixed 
// rather than dynamically allocated.
//
////////////////////////////////////////////////////////////////////////////////

SensorReadings sensorReadings;
AuxiliaryInput auxInput;
MotorControl baseControl;
MotorControl sensorControl;

////////////////////////////////////////////////////////////////////////////////
//
// Cooperative Multitasking System
//
////////////////////////////////////////////////////////////////////////////////

MotorProcess baseMotorProcess;
MotorProcess sensorMotorProcess;
AuxiliaryInputProcess auxInputProcess;
SensorProcess sensorProcess;
DiagnosticProcess diagnosticProcess;

static const byte ProcessCount = 5;
SCMProcess* processList[ProcessCount];
SCMScheduler scheduler(processList, ProcessCount);

void setup()
{
  Serial.begin(9600);
  
  CalibrationVectors[0] = BlueCalibrationData;
  CalibrationVectors[1] = RedCalibrationData;
  CalibrationVectors[2] = YellowCalibrationData;
  CalibrationVectors[3] = GreenCalibrationData;
  sensors.configure(SensorCount, sources, CalibrationVectorSize, CalibrationVectors, Aperture);

  processList[0] = NULL;// &baseMotorProcess;
  processList[1] = NULL;//&sensorMotorProcess;
  processList[2] = &auxInputProcess;
  processList[3] = &sensorProcess;
  processList[4] = &diagnosticProcess;
  
  diagnosticProcess.configure(&auxInput, &sensorReadings);
  sensorProcess.configure(&sensors, &sensorReadings);
  auxInputProcess.configure(AuxillaryInputPin, &auxInput);
  baseMotorProcess.configure(LowerServoPin, &baseControl, BaseServoLowBound, BaseServoMidpoint, BaseServoUpperBound);
  sensorMotorProcess.configure(UpperServoPin, &sensorControl, SensorServoLowBound, SensorServoMidpoint, SensorServoUpperBound);  
}

void loop()
{
  scheduler.run();
}

