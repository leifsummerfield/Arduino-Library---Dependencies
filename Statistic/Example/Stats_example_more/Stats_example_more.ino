//Statistic();		// constructor
//    http://playground.arduino.cc/Main/Statistics#.Uzo4DNy5duY
//Thanks to  robtillaart
//	void clear();		// reset all counters
//	void add(float);	// add a new value
//	long count();		// # values added
//	float sum();		// total
//	float minimum();	// minimum
//	float maximum();	// maximum
//	float average();	// average
//	float pop_stdev();	// population std deviation
//	float unbiased_stdev();	// unbiased std deviation 
//


#include "Statistic.h"  // without trailing s

Statistic myStats; 

void setup(void) 
{
  Serial.begin(9600);
  Serial.print("Demo Statistic lib ");
  Serial.println(STATISTIC_LIB_VERSION);
  myStats.clear(); //explicitly start clean
}

void loop(void) 
{
  long rn = random(0, 100);
  myStats.add(rn/100.0);

  Serial.print("  Count: ");
  Serial.print(myStats.count()); 

  Serial.print("  Average: ");
  Serial.print(myStats.average(), 4);

  Serial.print("  Std deviation: ");

  Serial.print(myStats.pop_stdev(), 4);
  Serial.println();

  if (myStats.count() == 300)
  {
   myStats.clear();
   delay(1000);
  }
}

