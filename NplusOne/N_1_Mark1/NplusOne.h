/*

  NplusOne.h - Library for ESI's N+1 motor control bus system
  Created by Leif Summerfield, September 3, 2013.
  
*/

#ifndef NplusOne_h
#define NplusOne_h

#include "Arduino.h"

class  NplusOne
{
  public:
    NPlusOne(int addr);
    void movePlus(int steps);
    int  step_pos();
  private:
  int _addr;

};

#endif
