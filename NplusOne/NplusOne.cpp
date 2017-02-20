


#include <Arduino.h>
#include "Wire.h"

#include "NplusOne.h"

//  int addr;

NplusOne::NplusOne(int addr)
{
  _addr = addr;
  Wire.begin();
  
}


void NplusOne::movePlus(int steps)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x2B);        // sends instruction byte
  Wire.write(highByte(steps));      //put 
  Wire.write(lowByte(steps));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}

void NplusOne::moveNeg(int steps)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x2D);        // sends instruction byte
  Wire.write(highByte(steps));      //put 
  Wire.write(lowByte(steps));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}


int NplusOne::readPos()
{
	//And here's a sequence to read motor position, and ping it out the serial port
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x3F);        // sends "read current steps" instruction
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(_addr,2);  

    while(Wire.available())    // slave may send less than requested
  { 
//___________________________HIGH BYTE___________________________________________
    char c = Wire.read(); // receive a byte as character 
    unsigned int d = c << 8;         //shift that sucker over 

//___________________________LOW BYTE___________________________________________
    c = Wire.read(); // receive a byte as character
    unsigned int e = int(c) & 0x00FF;
 
    //  OR the two bytes
    int f = e | d;            //bitwise OR of low byte and hight byte
	return f;
  }
}  	  

void NplusOne::home()
{
	Wire.beginTransmission(_addr); // transmit to device #_addr
	Wire.write(0x48);        // sends instruction byte "H"
	Wire.endTransmission();    // stop transmitting
	delay(100);
}	

void NplusOne::moveTo(int steps)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x4D);        // sends instruction byte
  Wire.write(highByte(steps));      //put 
  Wire.write(lowByte(steps));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}


void NplusOne::moveToBlock(int steps)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x4D);        // sends instruction byte
  Wire.write(highByte(steps));      //put 
  Wire.write(lowByte(steps));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
  
  //Now we're going to stay in a loop until we get a status that' not moving (ie not dec48)
  int Status = status();
  while(Status == 48)
  {
	digitalWrite(13,HIGH);
    Status = status();
    delay(50);
  }
  
     digitalWrite(13,LOW);
}


void NplusOne::BlockTillDone()
{

  //Now we're going to stay in a loop until we get a status that' not moving (ie not dec48)
  int Status = status();
  while(Status == 48)
  {
	digitalWrite(13,HIGH);
    Status = status();
    delay(50);
  }
  
     digitalWrite(13,LOW);
}




int NplusOne::status()
{
	//And here's a sequence to read motor status
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x73);        // sends "read current steps" instruction
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(_addr,2);  

    while(Wire.available())    // slave may send less than requested
  { 
//___________________________HIGH BYTE___________________________________________
    char c = Wire.read(); // receive a byte as character 
    unsigned int d = c << 8;         //shift that sucker over 

//___________________________LOW BYTE___________________________________________
    c = Wire.read(); // receive a byte as character
    unsigned int e = int(c) & 0x00FF;
 
    //  OR the two bytes
    int f = e | d;            //bitwise OR of low byte and hight byte
	return f;
	
	/*here's the decode secret
		switch (temp)
	{
		case 0:
		temp =  0x20;
		break;

		case 1:
		temp =  0x30;
		break;
		
		case 2:
		temp =  0x30;
		break;
		
		case 3:
		temp =  0x22;
		break;
		
		case 4:
		temp =  0x21;
		break;
		
		where case 1-4 is enumerated as such
		    
    {    0      1         2          3         4 
        IDLE, MOVE_CW, MOVE_CCW, MAX_LIMIT, MIN_LIMIT
		0x20	0x30	0x30		0x22		0x21
    };
	
	*/			
	
	
  }
}  	  


void NplusOne::stop()
{
	Wire.beginTransmission(_addr); // transmit to device #_addr
	Wire.write(0x48);				// sends instruction byte "h" to halt motor
	Wire.endTransmission();    // stop transmitting
}	


void NplusOne::setMax(int maxsteps)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x2C);        // sends instruction byte
  Wire.write(highByte(maxsteps));      //put 
  Wire.write(lowByte(maxsteps));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}


void NplusOne::setHomeOffset(int offset)
{
  Wire.beginTransmission(_addr); // transmit to device #_addr
  Wire.write(0x2E);        // sends instruction byte
  Wire.write(highByte(offset));      //put 
  Wire.write(lowByte(offset));      //put data here ( 16 bit ) 
  Wire.endTransmission();    // stop transmitting
}
