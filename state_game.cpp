#include "state_game.h"

bool gameHasInit = false;
unsigned short gameframeCounter = 0;

void Game()
{
	if(!gameHasInit)
	{
		Game_Init(); // One-time initialization of menu state.
		gameHasInit = true;
	}
	
	Game_Input();
	Game_Update();
	Game_Draw();
	
	gameframeCounter++; // Update frame counter for this state, resetting whenever it hits 32.
	if(gameframeCounter > 32)
	{
		gameframeCounter = 0;
	}
}

void Game_Init()
{
	// Set graphics mode to Mode 0 - Tiled Mode with Objects
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ;
	// Set up backgrounds
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;	
	REG_BG3CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;	
	
	// Load Palette and fill charblock 0
	memcpy(pal_bg_mem, prototype_gfxPal, prototype_gfxPalLen);
	
	memcpy(&tile_mem[0][0], prototype_gfxTiles, prototype_gfxTilesLen);

	

}

void Game_Input()
{
	//Pushing start will push the Game state onto the stack, starting the game.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		//Push Pause State
		
	}
	
}

void Game_Update()
{
	//Game logic goes here
	
}

void Game_Draw()
{
	//Game draw routines go here
}

void Game_Offload()
{
	// Clear stuff out, pop stack
}
