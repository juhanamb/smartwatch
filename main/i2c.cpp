// Function implementation for i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro_init; 

void init_i2c() {
 Wire.begin(); // join I2C bus
 Serial.begin(750); // initialize serial communication
 Serial.println("Initializing I2C devices...");
 accelgyro_init.initialize();

 // verify connection
 Serial.println("Testing device connections...");
 Serial.println(accelgyro_init.testConnection() ? "MPU6050 connection successful": "MPU6050 connection failed");

}