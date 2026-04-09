#include "NHD_US2066.h"


const char slave2w = 0x3D;  //3C or 78
unsigned char mode = 1; // 0 = 8-bit parallel 6800 mode; 1 = i2c mode; 2 = SPI mode;
unsigned char tx_packet[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
TwoWire I2C_1 = TwoWire(1);

void command(unsigned char c)
{
  unsigned char i, temp;
  switch(mode)
  {
   case 1:    tx_packet[0] = 0x00;
              tx_packet[1] = c;
              send_packet(2);
              break;
  }
  
}
void data(unsigned char d)
{
  unsigned char i, temp;
  switch(mode)
  {
   case 1:    tx_packet[0] = 0x40;
              tx_packet[1] = d;
              send_packet(2);
              break;
  }
  
}

void send_packet(unsigned char x)
{
  unsigned char ix;
  
  I2C_1.beginTransmission(slave2w);
  for(ix=0;ix<x;ix++)
  {
    I2C_1.write(tx_packet[ix]);
  }
  I2C_1.endTransmission();
}

void init_oled()
{
  pinMode(ASCL, OUTPUT);      //set Arduino I2C lines as outputs
  pinMode(ASDA, OUTPUT);      //
  pinMode(11, OUTPUT); // SA0
  pinMode(RES, OUTPUT); 
  digitalWrite(ASCL, LOW);    //
  digitalWrite(ASDA, LOW);    //
  digitalWrite(RES, HIGH);
  digitalWrite(11, HIGH); //SA0
  delay(10);
  I2C_1.begin(9, 8);
  delay(10);
  mode = 1; // Set to I2C mode
  Serial.println("Reset HIGH");
  command(0x2A);  //function set (extended command set)
	command(0x71);  //function selection A, disable internal Vdd regualtor
	data(0x00);
	command(0x28);  //function set (fundamental command set)
	command(0x08);  //display off, cursor off, blink off
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xD5);  //set display clock divide ratio/oscillator frequency
	command(0x70);  //set display clock divide ratio/oscillator frequency
	command(0x78);  //OLED command set disabled
	command(0x09);  //extended function set (4-lines)
  command(0x06);  //COM SEG direction
	command(0x72);  //function selection B, disable internal Vdd regualtor
	data(0x00);     //ROM CGRAM selection
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xDA);  //set SEG pins hardware configuration
	command(0x0);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0xDC);  //function selection C
	command(0x00);  //function selection C
	command(0x81);  //set contrast control
	command(0x7F);  //set contrast control
	command(0xD9);  //set phase length
	command(0xF1);  //set phase length
	command(0xDB);  //set VCOMH deselect level
	command(0x40);  //set VCOMH deselect level
	command(0x78);  //OLED command set disabled
	command(0x28);  //function set (fundamental command set)
	command(0x01);  //clear display
	command(0x80);  //set DDRAM address to 0x00
	command(0x0C);  //display ON
  Serial.println("Display on");
  delay(100);

}