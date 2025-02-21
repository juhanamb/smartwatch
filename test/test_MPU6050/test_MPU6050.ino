// Separate code for testing MPU6050 IMU connectivity and functionality
// 
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int16_t ax, ay, az; // define accel as ax,ay,az
int16_t gx, gy, gz; // define gyro as gx,gy,gz
int16_t ay_indicator[10];

#define LED_PIN 13
bool blinkState = false;

void setup() {
 pinMode(2,OUTPUT); 
 Wire.begin(); // join I2C bus
 Serial.begin(750); // initialize serial communication
 Serial.println("Initializing I2C devices...");
 accelgyro.initialize();

 // verify connection
 Serial.println("Testing device connections...");
 Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful"
: "MPU6050 connection failed");
 pinMode(LED_PIN, OUTPUT); // configure LED pin
}

void loop() {
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


 if (abs(ay) > 1000) {
  Serial.println("Motion detected!");

 } 
 // blink LED to indicate activity
 blinkState = !blinkState;
 digitalWrite(LED_PIN, blinkState);
}
