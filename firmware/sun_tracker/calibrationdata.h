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

static const byte CalibrationVectorSize = 12;
static const int Aperture[CalibrationVectorSize]              = {19, 29,  37,  53,  70,  79,  90, 103, 113, 121, 131, 136};
static const int BlueCalibrationData[CalibrationVectorSize]   = {30, 82, 105, 260, 456, 553, 650, 780, 828, 858, 904, 923};
static const int RedCalibrationData[CalibrationVectorSize]    = {22, 59,  85, 199, 380, 494, 596, 725, 770, 798, 880, 905};
static const int YellowCalibrationData[CalibrationVectorSize] = {22, 63,  89, 221, 410, 513, 624, 752, 799, 822, 892, 915};
static const int GreenCalibrationData[CalibrationVectorSize]  = {28, 74,  90, 233, 423, 532, 621, 760, 814, 846, 897, 915};

#endif//CALIBRATION_DATA_H

