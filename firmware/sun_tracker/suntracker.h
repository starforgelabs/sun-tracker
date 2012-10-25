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

#ifndef SUNTRACKER_H
#define SUNTRACKER_H

#include "Arduino.h"

// These are project-specific constants. 

// Analogue inputs
static const byte BlueSensorPin = 5;
static const byte RedSensorPin = 4;
static const byte YellowSensorPin = 3;
static const byte GreenSensorPin = 2;
static const byte AuxillaryInputPin = 1;

// Digital outputs
static const byte LEDPin = 5;
static const byte LowerServoPin = 10;
static const byte UpperServoPin =  9;

// The motors were experimented with to determine their 
// range of motion and their observed "zero" (neutral, 
// or mid-point) values. 
static const int BaseServoLowBound = 600;
static const int BaseServoMidpoint = 1600;
static const int BaseServoUpperBound = 2400;

static const int SensorServoLowBound = 640;
static const int SensorServoMidpoint = 1575;
static const int SensorServoUpperBound = 2330;

#endif // SUNTRACKER_H

