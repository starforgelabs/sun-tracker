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

#ifndef CALIBRATION_DATA_H
#define CALIBRATION_DATA_H

#include "suntracker.h" 

static const byte SensorCount = 4;
const static byte SensorPins[SensorCount] = {BlueSensorPin, RedSensorPin, YellowSensorPin, GreenSensorPin};

static const byte CalibrationVectorSize = 16;
static const int Aperture[CalibrationVectorSize]              = {150, 124, 114, 106, 98, 88,  76,  64,  59,  55,  49,  44,  39,  32,  13,  -9 };
static const int BlueCalibrationData[CalibrationVectorSize]   = {  5,   9,  16,  24, 30, 47,  88, 127, 161, 180, 213, 284, 376, 499, 713, 959 };
static const int RedCalibrationData[CalibrationVectorSize]    = {  7,  18,  27,  39, 47, 73, 141, 196, 228, 256, 309, 379, 483, 616, 803, 981 };
static const int YellowCalibrationData[CalibrationVectorSize] = {  5,  16,  24,  33, 43, 66, 132, 177, 220, 253, 289, 385, 465, 600, 813, 980 };
static const int GreenCalibrationData[CalibrationVectorSize]  = {  7,  14,  23,  32, 42, 65, 123, 168, 213, 241, 274, 371, 450, 575, 789, 970 };

#endif//CALIBRATION_DATA_H

