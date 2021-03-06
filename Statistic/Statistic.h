#ifndef Statistic_h
#define Statistic_h
// 
//    FILE: Statistic.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
//          modified at 0.3 by Gil Ross at physics dot org
// PURPOSE: Recursive Statistical library for Arduino
// VERSION: 0.3.00
//     URL: http://www.arduino.cc/playground/Main/Statistics
// HISTORY: See Statistic.cpp
//
// Released to the public domain
//

// the standard deviation increases the lib (<100 bytes)
// it can be in/excluded by un/commenting next line
#define STAT_USE_STDEV

#define STATISTIC_LIB_VERSION "0.3.1"

#ifdef STAT_USE_STDEV
#include <math.h>
#endif

class Statistic 
{
	public:
	Statistic();
	void clear();
	void add(float);
	long count();
	float sum();
	float average();
	float minimum();
	float maximum();


#ifdef STAT_USE_STDEV
	float pop_stdev();	    // population stdev
	float unbiased_stdev();
#endif

protected:
	long _cnt;
	float _store;           // store to minimise computation
	float _sum;
	float _min;
	float _max;
#ifdef STAT_USE_STDEV
	float _ssqdif;		    // sum of squares difference
#endif
};

#endif
// END OF FILE