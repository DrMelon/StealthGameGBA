#include "state_game.h"

bool gameHasInit = false;
unsigned short gameframeCounter = 0;
Player* thePlayer = 0;

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
	REG_BG3CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;	
	
	// Load Palette
	memcpy(pal_bg_mem, prototype_gfxPal, prototype_gfxPalLen);
	// Copy to Sprite Palette
	memcpy(pal_obj_mem, pal_bg_mem, prototype_gfxPalLen);
	// Fill charblock 0
	memcpy(&tile_mem[0][0], prototype_gfxTiles, prototype_gfxTilesLen);

	// Clear Screenblocks 
	memcpy(&se_mem[30], Background, sizeof(u16)*32*32); // Fill BG3 with Background (wallpaper) tiles
	memcpy(&se_mem[29][0], Blank, sizeof(u16)*32*32); // Filling the others with Blank tiles.
	memcpy(&se_mem[28][0], Blank, sizeof(u16)*32*32); // 
	memcpy(&se_mem[27][0], Blank, sizeof(u16)*32*32); // 
	
	// Load Level 1 Layout into BG1
	memcpy(&se_mem[29][0], Level1, sizeof(u16)*32*32);
	
	// Initialize Object Buffer
	InitializeObjects();
	
	// Copying tiles from charblock 0 to charblock 4
	tile_mem[4][0] = tile_mem[0][26]; // Player Idle Tile is 13 (26 in 4bpp tiles) - Making it into tile 0 here, as it is the most important tile.
	tile_mem[4][1] = tile_mem[0][27]; // Because TONC handles tiles in 4bpp mode usually, I have to copy both halves of the tile.
	
	// Create Player object
	thePlayer = new Player(32, 32, (u16**)Level1);
	
	// Set up Maximum Speed
	thePlayer->MaxVelocity.X = 2;
	thePlayer->MaxVelocity.Y = 6;

	

}

void Game_Input()
{
	//Pushing start will push the Game state onto the stack, starting the game.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		//Push Pause State
		
	}
	
	if(key_is_down(KEY_LEFT))
	{
		thePlayer->Acceleration.X = -0.1;
	}
	else if(key_is_down(KEY_RIGHT))
	{
		thePlayer->Acceleration.X = 0.1;
	}
	else
	{
		thePlayer->Acceleration.X = 0;
	}
	
	if(key_hit(KEY_A))
	{
		//Check to see if we can jump
		thePlayer->Velocity.Y = -4;
	}
	
}

void Game_Update()
{
	//Game logic goes here
	thePlayer->Update();
}

void Game_Draw()
{
	//Game draw routines go here
	thePlayer->Draw();
	
	// Update Objects
	UpdateObjects();
}

void Game_Offload()
{
	// Clear stuff out, pop stack
}
