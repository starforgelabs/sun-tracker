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

// TODO: It looks like I don't have any valid sensor data. These values are garbage. Just redo them.
static const byte CalibrationVectorSize = 10;
static const int Aperture[CalibrationVectorSize]              = {00,  30,  43,  54,  65,  74,  90, 100, 123, 133};
static const int BlueCalibrationData[CalibrationVectorSize]   = {34, 189, 317, 425, 559, 663, 805, 871, 933, 960};
static const int RedCalibrationData[CalibrationVectorSize]    = {26, 157, 292, 435, 549, 649, 793, 863, 930, 972};
static const int YellowCalibrationData[CalibrationVectorSize] = {36, 187, 326, 420, 581, 688, 827, 885, 951, 978};
static const int GreenCalibrationData[CalibrationVectorSize]  = {26, 146, 265, 395, 515, 613, 760, 834, 978, 970};

#endif//CALIBRATION_DATA_H

