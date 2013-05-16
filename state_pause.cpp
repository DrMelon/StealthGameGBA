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
	
	
	Pause_Update();
	Pause_Draw();
	Pause_Input();
	
	pauseframeCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(pauseframeCounter > 32)
	{
		pauseframeCounter = 0;
	}
}

void Pause_Init()
{

	// Copy PAUSED graphics to CB2
	memcpy(&tile_mem[2][192], pausestuffTiles, pausestuffTilesLen);
	
	
	
	


}

void Pause_Input()
{
	//Pushing start will push the Pause state onto the stack, starting the pause.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		// Pop pause state & offload
		Pause_Offload();
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
	// Write "PAUSED" on BG0.
	SetTile(27, 10, 10, 96);
	SetTile(27, 12, 10, 97);
	SetTile(27, 14, 10, 98);
	SetTile(27, 16, 10, 99);
	SetTile(27, 18, 10, 100);
	SetTile(27, 20, 10, 101);
	
	// Update Objects
	UpdateObjects();
}

void Pause_Offload()
{
	// Clear BG0
	memcpy(&se_mem[27][0], Blank, sizeof(u16)*32*32);
}
