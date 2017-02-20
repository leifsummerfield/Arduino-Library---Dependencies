/*

  NplusOne.cpp - Library for ESI's N+1 motor control bus system
  Created by Leif Summerfield, September 3, 2013.
  
*/


#include "Arduino.h"
#include "NplusOne.h"


NplusOne::NplusOne(int addr);
{
    Wire.begin(); // join i2c bus (address optional for master)
    _addr = addr;
}


void movePlus(int steps);
{
  // //Here's a write sequence to home the motor
  Wire.beginTransmission(_addr); // transmit to device #4
  Wire.send(0x2B);        // sends instruction byte to move in positive direction some releative number of steps
  Wire.send(0x00);      //put high byte here
  Wire.send(0x64);      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}


int  step_pos();
{
  Wire.beginTransmission(_addr); // transmit to device #4
  Wire.send(0x3F);        // sends "read current steps" instruction
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(_addr,2);  

    while(Wire.available())    // slave may send less than requested
  { 
//___________________________HIGH BYTE___________________________________________
    char c = Wire.receive(); // receive a byte as character 
    unsigned int d = c << 8;         //shift that sucker over 

//___________________________LOW BYTE___________________________________________
    c = Wire.receive(); // receive a byte as character
    unsigned int e = int(c) & 0x00FF;
 
    //  OR the two bytes
    int f = e | d;            //bitwise OR of low byte and hight byte  
    return(f);
    }
   
} 
