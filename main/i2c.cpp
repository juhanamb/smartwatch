// Function implementation for i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MAX30105.h"
#include "sensorFunctions.h"

TwoWire I2C_1 = TwoWire(1);

MPU6050 accelgyro; 
MAX30105 particleSensor;

lm75b_handle_t lm75b_handle;

// I2C callback functions for LM75B using I2C_1
uint8_t lm75b_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
  I2C_1.beginTransmission(addr);
  I2C_1.write(reg);
  for (uint16_t i = 0; i < len; i++) {
    I2C_1.write(buf[i]);
  }
  return I2C_1.endTransmission();
}

uint8_t lm75b_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len) {
  I2C_1.beginTransmission(addr);
  I2C_1.write(reg);
  I2C_1.endTransmission(false);
  I2C_1.requestFrom(addr, (size_t)len);
  for (uint16_t i = 0; i < len; i++) {
    buf[i] = I2C_1.read();
  }
  return 0; // Assume success
}

void init_i2c() {
  pinMode(13, OUTPUT);      //set Arduino I2C lines as outputs
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);      //set Arduino I2C lines as outputs
  pinMode(8, OUTPUT);

  Wire.begin(13, 12); // join I2C bus with 13 (SDA) and 12 (SCL) pins
  I2C_1.begin(9, 8); // join I2C bus with 9 (SDA) and 8 (SCL) pins
  Serial.begin(115200); // initialize serial communication


  Serial.println("Initializing I2C devices...");
  Serial.println("Initializing MAXREFDES117...");

  // Initialize I2C and MAX30102
  if (!particleSensor.begin(I2C_1, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  Serial.println("Initializing MPU6050 device...");
  accelgyro.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful": "MPU6050 connection failed");

  // // Initialize LM75B on I2C_1
  // lm75b_handle.iic_write = lm75b_iic_write;
  // lm75b_handle.iic_read = lm75b_iic_read;
  // lm75b_handle.iic_addr = 0x90; // Default LM75B address
  // lm75b_init(&lm75b_handle);

}