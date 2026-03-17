#ifndef SENSORFUNCTIONS_H
#define SENSORFUNCTIONS_H

#include "driver_lm75b.h"

// FSM States
enum State {
  SLEEP,
  INIT, 
  READ_IMU,
  READ_TEMP,
  READ_HR,  
  SET_IL,
  UPDATE,
};

// Declare the global state variable (defined in sensorFunctions.cpp)
extern State STATE;

extern lm75b_handle_t lm75b_handle;

void readMPU6050();
float readTemperature();
int readHR();
void setIntenstity();
void updateScreen();
void printToScreen(const char* str);

#endif 