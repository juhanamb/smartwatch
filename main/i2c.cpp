// Function implementation for i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro; 

void init_i2c() {
 Wire.begin(); // join I2C bus
 Serial.begin(750); // initialize serial communication
 Serial.println("Initializing I2C devices...");
 accelgyro.initialize();

 // verify connection
 Serial.println("Testing device connections...");
 Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful": "MPU6050 connection failed");

}