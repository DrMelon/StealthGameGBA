#include "state_menu.h"

bool menuHasInit = false;
unsigned short menuframeCounter = 0;

void Menu()
{
	if(!menuHasInit)
	{
		Menu_Init(); // One-time initialization of menu state.
		menuHasInit = true;
	}
	
	Menu_Input();
	Menu_Update();
	Menu_Draw();
	
	menuframeCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(menuframeCounter > 32)
	{
		menuframeCounter = 0;
	}
}

void Menu_Init()
{
	// Set graphics mode to Mode 4 - Palette-Based Bitmap Mode
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	
	// Load palette from file
	memcpy(pal_bg_mem, title_screenPal, title_screenPalLen);	
	
	// Load graphics from file
	memcpy(vid_mem, title_screenBitmap, title_screenBitmapLen);
	

}

void Menu_Input()
{
	//Pushing start will push the Game state onto the stack, starting the game.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		//Push game state on after offloading this state.
		Menu_Offload();
		State nextState;
		nextState.StatePointer = Game;
		g_StateStack->states.push(nextState);
	}
	
}

void Menu_Update()
{
	//Use the framecounter to slow this down a little.
	if(menuframeCounter % 4 != 0) return;

	// Cycle palette colours 12-20
	
	unsigned short firstColourIndex = pal_bg_mem[12];
	for(int i = 12; i < 20; i++)
	{
		pal_bg_mem[i] = pal_bg_mem[i+1]; // shift the colours left
	}
	// Set colour 19 to original colour 12 to continue the cycle.
	pal_bg_mem[20] = firstColourIndex;	
	
}

void Menu_Draw()
{
	//Nothing to be done.
}

void Menu_Offload()
{
	//menuHasInit = false;
	
	memset(vid_mem, 0, 76800); // Wipe Video Memory
	memset(pal_bg_mem, 0, 64); // Clear Palette
}
