// Header file for i2c functions
#ifndef I2C_H
#define I2C_H
#include "MPU6050.h"
#include "driver_lm75b.h"
#include "MAX30105.h"

// Give instance visibility to all files
extern MPU6050 accelgyro;
extern MAX30105 HRsensor;

// i2c functions
void init_i2c();

#endif