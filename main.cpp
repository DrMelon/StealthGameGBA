

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" // Using TONC - Note that some files may have been edited by me to work better.
#include "statestack.h" // Game State Stack - basically for handling game states.

//Game State Includes
#include "state_menu.h"
#include "state_game.h"


int main()
{

	
	// Enable IRQ Interrupts
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	// Initialize Game State Manager with Menu State
	State startState;
	startState.StatePointer = Menu;
	g_StateStack->states.push(startState);
	
	
	while(true)
	{
		VBlankIntrWait(); // IRQ-enabled VSync
		
		// Run Current State
		g_StateStack->states.top().StatePointer();
		
		
		
	}
	
	return 0;
}