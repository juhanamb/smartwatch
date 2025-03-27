#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "i2c.h"
#include "sensorFunctions.h"
#include "driver_lm75b.h"
#include "MAX30105.h"

uint8_t tmp = 0;

void setup() {
  // Initialize i2c connection. At the moment only MPU6050 is initialized for pins 35, 36
  init_i2c();
}


void loop() {
  // Main logic 
  // This will be following the FSM pick in the spec
  // At the moment, READ_IMU(update theshold value) -> READ_BATTERY -> SET_IL based on theshold -> UPDATE, print the IL in serial monitor
  
  Serial.print("STATE: ");
  Serial.println(STATE);
  switch (STATE) {
    case INIT:
        break;
    case READ_IMU:  
        readMPU6050();
        break;
        //temperature = float readTemperature();
        //HR = readHR();
    case READ_BATTERY:
        tmp = readBatteryLevel();
        break;
    case SET_IL:
        setIntenstity();
        break;
    case UPDATE:
        updateScreen();
        break; 
  } 
}
