



#ifndef NplusOne_h
#define NplusOne_h

#include "Wire.h"

class NplusOne
{
  public:
  
	NplusOne(int addr);
	
	void	movePlus(int steps);
	void	moveNeg(int steps);
	int		readPos();
	int		status();
	void	home();	
	void	stop();
	void	moveTo(int steps);
	void    moveToBlock(int steps);
	void	BlockTillDone();
	
	void	setMax(int maxsteps);
	void	setHomeOffset(int offset);
	
	
  private:
	int _addr;

};
#endif
