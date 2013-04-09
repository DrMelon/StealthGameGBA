
// Using TONC - Note that some files may have been edited by me to work better.
#include "tonclib/include/tonc.h"
#include <string.h>
#include <stdlib.h>


int main()
{

	// Set up Display
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;
	REG_BG3CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;
	
	
	// Enable IRQ Interrupts
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	while(true)
	{
		VBlankIntrWait();
		
		
		
		
	}
	
	return 0;
}