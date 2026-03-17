// Function implementation for i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MAX30105.h"
#include "sensorFunctions.h"

TwoWire I2C_1 = TwoWire(1);

MPU6050 accelgyro; 
MAX30105 HRsensor;

lm75b_handle_t lm75b_handle;

// I2C callback functions for LM75B using Wire1
uint8_t lm75b_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
  Wire1.beginTransmission(addr);
  Wire1.write(reg);
  for (uint16_t i = 0; i < len; i++) {
    Wire1.write(buf[i]);
  }
  return Wire1.endTransmission();
}

uint8_t lm75b_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
  Wire1.beginTransmission(addr);
  Wire1.write(reg);
  Wire1.endTransmission(false);
  Wire1.requestFrom(addr, (size_t)len);
  for (uint16_t i = 0; i < len; i++) {
    buf[i] = Wire1.read();
  }
  return 0; // Assume success
}

void init_i2c() {
  Wire.begin(13, 12); // join I2C bus with 13 (SDA) and 12 (SCL) pins
  Wire1.begin(9, 8); // join I2C bus with 14 (SDA) and 15 (SCL) pins
  Serial.begin(115200); // initialize serial communication


  Serial.println("Initializing I2C devices...");
  Serial.println("Initializing MAXREFDES117...");

  // Initialize I2C and MAX30102
  if (!HRsensor.begin(Wire1, I2C_SPEED_STANDARD)) {
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

  // Initialize LM75B on Wire1
  lm75b_handle.iic_write = lm75b_iic_write;
  lm75b_handle.iic_read = lm75b_iic_read;
  lm75b_handle.iic_addr = 0x90; // Default LM75B address
  lm75b_init(&lm75b_handle);

  STATE = READ_IMU;
}