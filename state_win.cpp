#include "state_win.h"

bool winHasInit = false;
unsigned short winframeCounter = 0;

void Win()
{
	if(!winHasInit)
	{
		Win_Init(); // One-time initialization of state
		winHasInit = true;
	}
	
	Win_Input();
	Win_Update();
	Win_Draw();
	
	winframeCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(winframeCounter > 32)
	{
		winframeCounter = 0;
	}
}

void Win_Init()
{
	// Set graphics mode to Mode 4 - Palette-Based Bitmap Mode
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	
	// Load palette from file
	memcpy(pal_bg_mem, businessPal, businessPalLen);	
	
	// Load graphics from file
	memcpy(vid_mem, businessBitmap, businessBitmapLen);
	

}

void Win_Input()
{
		
}

void Win_Update()
{
		
}

void Win_Draw()
{
	//Nothing to be done.
}

void Win_Offload()
{
	memset(vid_mem, 0, 76800); // Wipe Video Memory
	memset(pal_bg_mem, 0, 64); // Clear Palette
}
