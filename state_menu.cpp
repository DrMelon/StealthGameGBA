#include "state_menu.h"

bool HasInit = false;
unsigned short frameCounter = 0;

void Menu()
{
	if(!HasInit)
	{
		Menu_Init(); // One-time initialization of menu state.
		HasInit = true;
	}
	
	Menu_Input();
	Menu_Update();
	Menu_Draw();
	
	frameCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(frameCounter > 32)
	{
		frameCounter = 0;
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
}

void Menu_Update()
{
	//Use the framecounter to slow this down a little.
	if(frameCounter % 4 != 0) return;

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