//
//    FILE: pcf8574_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 27-08-2013
//
// PUPROSE: demo 
//

#include "PCF8574.h"
#include <Wire.h>

// adjust addresses if needed
PCF8574 PCF_39(0x20);  // add leds to lines      (used as output)
  int pincounter = 1; 
  int value; 
  
void setup()
{
  Serial.begin(115200);
  Serial.println("\nTEST PCF8574\n");

  uint8_t value = PCF_39.read8();
  Serial.print("#38:\t");
  Serial.println(value);

}

void loop()
{
  // echos the lines

  PCF_39.writeBit(pincounter,HIGH);
  pincounter++;
    value = PCF_39.read8(); 
      Serial.println(value);
          
  delay(50);
  if(pincounter > 16) {
    pincounter = 1;
  }
}
//
// END OF FILE
//
