// Function implementation for i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MAX30105.h"

MPU6050 accelgyro; 
MAX30105 HRsensor;

void init_i2c() {
  Wire.begin(35, 36); // join I2C bus with 35 (SDA) and 36 (SCL) pins
  Serial.begin(115200); // initialize serial communication
  Serial.println("Initializing I2C devices...");
  Serial.println("Initializing MAXREFDES117...");

  // Initialize I2C and MAX30102
  if (!HRsensor.begin(Wire, I2C_SPEED_STANDARD)) {
      Serial.println("MAXREFDES117 not found. Check wiring!");
  //    while (1); TBD: REMOVE THIS when we get the sensro
  } 
  // Configure the sensor TBD 
/*  HRsensor.setup();
  HRsensor.setPulseAmplitudeRed(0x0A);  // IR LED Current
  HRsensor.setPulseAmplitudeIR(0x0A);   // Red LED Current */
  Serial.println("Initializing MPU6050 device...");
  accelgyro.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful": "MPU6050 connection failed");

}