#include "sensorFunctions.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "i2c.h"
#include "driver_lm75b.h"
#include "MAX30105.h"
#include "NHD_US2066.h"
#include "heartRate.h"

#define ANALOG_PIN 35

int16_t ax, ay, az; // define accel as ax,ay,az
int16_t gx, gy, gz; // define gyro as gx,gy,gz
int16_t imu_threshold = 0;
int16_t ay_indicator[10];
int8_t IL = 0;

// MAX30105
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

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
    Serial.println(az);*/
    Serial.print("\t"); 
    Serial.print(gx);
    Serial.print("\t");
    Serial.print(gy);
    Serial.print("\t");
    Serial.println(gz); 

    // Add up to IMU threshold value 
    delay(500);
    imu_threshold = imu_threshold + abs(ay);
  }
  // Calculate average IMU values
  imu_threshold = imu_threshold / 10;
  Serial.print("imu_threshold: ");
  Serial.println(imu_threshold);
  STATE = READ_TEMP;
}

// Sensorfunction definitions 

float readTemperature() {
  // Read temperature sensor using LM75B
  uint16_t raw;
  float temp;
  lm75b_read(&lm75b_handle, &raw, &temp);
  Serial.print("Temperature: ");
  Serial.println(temp);
  STATE = READ_HR;
  return temp;
}

int readHR() {
  long irValue = particleSensor.getIR();
  Serial.println("In READ HR");
  for (int i = 0; i < 100; i++) {
    irValue = particleSensor.getIR();
    if (checkForBeat(irValue) == true)
    {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
      Serial.print("IR=");
      Serial.print(irValue);
      Serial.print(", BPM=");
      Serial.print(beatsPerMinute);
      Serial.print(", Avg BPM=");
      Serial.print(beatAvg);

      if (irValue < 50000)
        Serial.print(" No finger?");    
    }
    else Serial.println("No beat detected");
  }
  STATE = SET_IL;
  return 0;
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
  STATE = READ_IMU;
}

void updateScreen() {
  // Write characters to screen
  // Format: 
  // HR120 walk IL:4 (Hear rate, activity type, intensity level)
  // -40°C B:100 % (Temperature, Battery level)
  command(0x01); // Clear display
  delay(10);
  char buffer[20];
  sprintf(buffer, "IL:%d", IL);
  printToScreen(buffer);
  STATE = READ_IMU;
}

void printToScreen(const char* str) {
  command(0x80); // Set DDRAM address to 0x00 (first line)
  for(int i = 0; str[i] != '\0'; i++) {
    data(str[i]);
  }
}