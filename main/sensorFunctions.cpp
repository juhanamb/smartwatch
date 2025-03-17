#include "sensorFunctions.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "i2c.h"
#include "driver_lm75b.h"
#include "MAX30105.h"

int16_t ax, ay, az; // define accel as ax,ay,az
int16_t gx, gy, gz; // define gyro as gx,gy,gz
int16_t imu_threshold = 0;
int16_t ay_indicator[10];
int8_t IL = 0;

State STATE = INIT; // Set STATE variable to first state (INIT)

void readMPU6050() {
  // Read IMU values
  // MPU6050 library is needed
  for (int i = 0; i < 10; i++) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // read measurements from device
    // display tab-separated accel/gyro x/y/z values
/*    Serial.print("a/g:\t");
    Serial.print(ax);
    Serial.print("\t");
    Serial.print(ay);
    Serial.print("\t");
    Serial.println(az);
    Serial.print("\t"); 
    Serial.print(gx);
    Serial.print("\t");
    Serial.print(gy);
    Serial.print("\t");
    Serial.println(gz); 
    delay(500);*/

    // Add up to IMU threshold value 
    delay(500);
    imu_threshold = imu_threshold + abs(ay);
  }
  // Calculate average IMU values
  imu_threshold = imu_threshold / 10;
  Serial.print("imu_threshold: ");
  Serial.println(imu_threshold);
  STATE = SET_IL;
}

// Sensorfunction definitions 

float readTemperature() {
  // Read temperature sensor 
}

int readBatteryLevel(){
  // Read battery voltage from resistor division 
  // Calculate battery level
}

int readHR() {
  // Read Heart Rate sensor 
  // Initially try to make it print to serial monitor
  // Sparkfun MAX3010x library for this is needed
    // Read sensor values
    long irValue = HRsensor.getIR();
    long redValue = HRsensor.getRed();

    Serial.print("IR: "); Serial.print(irValue);
    Serial.print("\tRed: "); Serial.println(redValue);

    // Basic check if finger is placed
    if (irValue < 50000) {
        Serial.println("No finger detected!");
    }

    delay(500);  // Delay for readability
}

void setIntenstity() {
  // Calculate intensity level
  // Add RGB led logic here based on intensity level

  /* 
  Case: Intensity [1,2,3,4,5] -> Set LED to be [White, Blue, Green, Yellow, Red]
  */
  // At the moment: Based only on IMU movements "ay" value. 
  // This will be replaced with more complex logic that follows up also HR
  if (imu_threshold > 500){
    IL = 1;
    Serial.println("IL set to 2");
  }
  else {
    IL = 2;
    Serial.println("IL set to 1");
  }
  imu_threshold = 0;
  STATE = UPDATE;
}

void updateScreen() {
  // Write characters to screen
  // Format: 
  // HR120 walk IL:4 (Hear rate, activity type, intensity level)
  // -40°C B:100 % (Temperature, Battery level)
  Serial.print("IL:");
  Serial.println(IL);
  STATE = READ_IMU;
}
