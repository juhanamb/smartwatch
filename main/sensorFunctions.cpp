#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "i2c.h"

//MPU6050 accelgyro;
int16_t ax, ay, az; // define accel as ax,ay,az
int16_t gx, gy, gz; // define gyro as gx,gy,gz
int16_t ay_indicator[10];

void readMPU6050() {
 accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // read measurements from device
 // display tab-separated accel/gyro x/y/z values
 Serial.print("a/g:\t");
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


/* if (abs(ay) > 1000) {
  Serial.println("Motion detected!");

 }*/ 
 // blink LED to indicate activity
// blinkState = !blinkState;
// digitalWrite(LED_PIN, blinkState);

/*
Here will be definitions for 
void readTemperature()
void readBatteryLevel()
void readHR()
void setIntenstity()
void updateScreen()
*/
}