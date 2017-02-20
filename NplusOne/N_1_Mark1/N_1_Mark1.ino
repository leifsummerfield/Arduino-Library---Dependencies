// N+1 Bus controller
// by Leif Summerfield

// Using I2C "wire" library to communicate with N+1 motor device bus
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

#include <Wire.h>

String inString = "";

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  
    // prints title with ending line break 
  Serial.println("N+1 Position"); 
}

byte x = 0;

void loop()
{
// //Here's a write sequence to home the motor
//  Wire.beginTransmission(1); // transmit to device #4
//  Wire.send(0x2B);        // sends instruction byte
//  Wire.send(0x00);      //put 
//  Wire.send(0x64);      //put data here ( 16 bit ) 
//  Wire.endTransmission();    // stop transmitting
//
//  delay(100);
//  
  
//And here's a sequence to read motor position, and ping it out the serial port
  Wire.beginTransmission(1); // transmit to device #4
  Wire.send(0x3F);        // sends "read current steps" instruction
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(1,2);  

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
     
    Serial.print("Position in steps "); 
    Serial.println(f);         // print the character
    
  }

  Serial.println("Done");
  Serial.println();
  Serial.println();
  delay(1500);
}
