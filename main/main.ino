#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "i2c.h"
#include "sensorFunctions.h"
#include "driver_lm75b.h"
#include "MAX30105.h"

void setup() {
  // Initialize i2c connection. At the moment only MPU6050 is initialized
  init_i2c();
  
}


void loop() {
  // Main logic
  readMPU6050();
  /* Here will be:
  Read other sensors 
  IL = setIntensity();
  temperature = float readTemperature();
  batterylevel = readBatteryLevel();
  HR = readHR();
  void updateScreen();

  */
}
