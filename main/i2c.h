// Header file for i2c functions
#ifndef I2C_H
#define I2C_H
#include "MPU6050.h"

// Give instance visibility to all files
extern MPU6050 accelgyro;

// i2c functions
void init_i2c();

#endif