//
//    FILE: pcf8574_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 27-08-2013
//
// PUPROSE: demo 
//

#include <Wire.h>

// adjust addresses if needed
  uint8_t _data;
  int _error;
  
  int value = 0; 
  int _address;
  int pincounter = 1; 


void setup()
{
  _address = 0x20; 
  Wire.begin();
  
  Serial.begin(115200);
  Serial.println("\nTEST PCF8574\n");
  Serial.print("#1:\t");
  
 
}

void loop()
{
  // echos the lines

  PCF_writeBit(pincounter,HIGH);
  pincounter++;
    value = PCF_read8(); 
      Serial.println(value);
          
  delay(50);
  if(pincounter > 16) {
    pincounter = 1;
  }
}
//______________________________________________________________
uint8_t PCF_read8()
{
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 1);

   _data = Wire.read();
  _error = Wire.endTransmission();
  return _data;
}


//_________________________//_________________________//_________________________//_________________________//_________________________
void PCF_write8(int value)
{
  Wire.beginTransmission(_address);
  _data = value;
  Wire.write(_data);
  Wire.write(0x00);
  _error = Wire.endTransmission();
}

//_________________________//_________________________//_________________________//_________________________//_________________________
void PCF_write16(int value)
{
  Wire.beginTransmission(_address);
  _data = value;
  Wire.write(lowByte(value));
  Wire.write(highByte(value));
  _error = Wire.endTransmission();
}

//_________________________//_________________________//_________________________//________________
void PCF_writeBit(uint8_t pin, boolean state)
{
  int IOdata; 
  pin--; //since counting is pin1 = shift 0 (1-1)
  if (state == LOW) 
  {
    IOdata &= ~(1<<pin);
  }
  else 
  {
    IOdata |= (1<<pin);
  }
  
  PCF_write16(IOdata); 
}

//
// END OF FILE
//
