#ifndef SENSORFUNCTIONS_H
#define SENSORFUNCTIONS_H

// FSM States
enum State {
  INIT, 
  READ_IMU,
  READ_HR,  
  SET_IL,
  UPDATE,
  READ_TEMP,
  READ_BATTERY
};

// Declare the global state variable (defined in sensorFunctions.cpp)
extern State STATE;

void readMPU6050();
float readTemperature();
int readBatteryLevel();
int readHR();
void setIntenstity();
void updateScreen();

#endif 