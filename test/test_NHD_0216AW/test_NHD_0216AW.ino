//---------------------------------------------------------
/*

NHD_0216AW_XB3.ino

Program for writing to Newhaven Display Slim OLEDs based on US2066 controller.

Pick one up today in the Newhaven Display shop!
------> http://www.newhavendisplay.com/oled-slim-character-oleds-c-119_825.html

This code is written for the Arduino Mega.

Copyright (c) 2015 - Newhaven Display International, Inc.

Newhaven Display invests time and resources providing this open source code,
please support Newhaven Display by purchasing products from Newhaven Display!

*/
//---------------------------------------------------------

#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
//#include <avr\io.h>

#include "NHD_US2066.h"
unsigned char text1[] = {" Please Support "};
unsigned char text2[] = {"  Open-Source   "};
unsigned char text3[] = {"   Hardware &   "};
unsigned char text4[] = {"   Software !!  "};

unsigned char text5[] = {"Newhaven Display"};
unsigned char text6[] = {" 2X16 Character "};
unsigned char text7[] = {"  Slim  Design  "};
unsigned char text8[] = {"----------------"};



void output()
{
	int i;

        command(0x01);
        delay(2);
        for(i=0;i<16;i++){
          data(text1[i]);
        }
        
        command(0xA0);
        for(i=0;i<16;i++){
          data(text2[i]);
        }

        delay(2000);

        command(0x01);
        delay(2);
        for (i=0;i<16;i++){
		data(text3[i]);
        }
	
        command(0xA0);
        for (i=0;i<16;i++){
		data(text4[i]);
        }

        delay(3500);
        
        command(0x01);
        delay(2);
        for(i=0;i<16;i++){
          data(text5[i]);
        }
        
        command(0xA0);
        for(i=0;i<16;i++){
          data(text6[i]);
        }

        delay(2000);

        command(0x01);
        delay(2);
        for (i=0;i<16;i++){
		data(text7[i]);
        }
	
        command(0xA0);
        for (i=0;i<16;i++){
		data(text8[i]);
        }

}

void blocks()
{
	int i;

        command(0x01);
        delay(2);

        for(i=0;i<16;i++){
          data(0x1F);
        }

        command(0xA0);
        for(i=0;i<16;i++){
          data(0x1F);
        }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);    
  init_oled();
}

void loop() 
{  
  while(1)
  {
    output();

    delay(2000);
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0) {
        Serial.print("I2C device found at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
        nDevices++;
      }
      else if (error==4) {
        Serial.print("Unknow error at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
      }    
    }
    if (nDevices == 0) {
      Serial.println("No I2C devices found\n");
    }
    else {
      Serial.println("done\n");
    }
    //blocks();
  }
}