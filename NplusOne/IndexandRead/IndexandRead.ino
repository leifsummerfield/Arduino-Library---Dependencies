


// N+1 Bus controller
// by Leif Summerfield

// Using I2C "wire" library to communicate with N+1 motor device bus
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this
// Refer to the "Wire Slave Receiver" example for use with this
// On an N+1 device wire the Arduino as follows
//N+1 Connector   Arduino
//  Pin #          Port
//      5   ---    A5     
//      6   ---    A4     
//      7   ---    GND     
//      8   ---    GND    
//      9   ---    +5V    
//      10  ---    Vin (+12V)


#include <NplusOne.h>
#include <Wire.h>

NplusOne  Xstage(1);

void setup()
{
  Serial.begin(9600);
  Serial.println("N+1 Position"); 
}

void loop()
{
  Xstage.movePlus(10);
  delay(100);

  int Position =  Xstage.readPos();
  Serial.println(Position);
  delay(1000);
}
