#include "state_pause.h"

bool pauseHasInit = false;
unsigned short pauseframeCounter = 0;


void Pause()
{
	if(!pauseHasInit)
	{
		Pause_Init(); // One-time initialization of menu state.
		pauseHasInit = true;
	}
	
	Pause_Input();
	Pause_Update();
	Pause_Draw();
	
	pauseframeCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(pauseframeCounter > 32)
	{
		pauseframeCounter = 0;
	}
}

void Pause_Init()
{

	// Set up text and write PAUSED text to screen.
	

}

void Pause_Input()
{
	//Pushing start will push the Pause state onto the stack, starting the pause.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		// Pop pause state & offload
		g_StateStack->states.pop();
	}
	
	
	
}

void Pause_Update()
{
	//Pause logic goes here
	
}

void Pause_Draw()
{
	//Pause draw routines go here
	
	// Update Objects
	UpdateObjects();
}

void Pause_Offload()
{
	// Clear stuff out, pop stack
}
