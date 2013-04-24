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
	
	Game_Update();
	Game_Input();
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
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
	// Set up backgrounds
	REG_BG3CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(1) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;	
	REG_BG0CNT = BG_CBB(2) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;	
	
	// Load Palette
	memcpy(pal_bg_mem, prototype_gfxPal, prototype_gfxPalLen);
	// Copy to Sprite Palette
	memcpy(pal_obj_mem, pal_bg_mem, prototype_gfxPalLen);
	// Fill charblock 0
	memcpy(&tile_mem[0][0], prototype_gfxTiles, prototype_gfxTilesLen);
	// Charblock 1
	memcpy(&tile_mem[1][0], shadowtiles_simpleTiles, shadowtiles_simpleTilesLen);

	// Clear Screenblocks 
	memcpy(&se_mem[30], Background, sizeof(u16)*32*32); // Fill BG3 with Background (wallpaper) tiles
	memcpy(&se_mem[29][0], Blank, sizeof(u16)*32*32); // Filling the others with Blank tiles.
	memcpy(&se_mem[28][0], Blank, sizeof(u16)*32*32); // 
	memcpy(&se_mem[27][0], Blank, sizeof(u16)*32*32); // 
	
	// Load Level 1 Layout into BG1
	memcpy(&se_mem[28][0], Level1, sizeof(u16)*32*32);
	
	// Initialize Object Buffer
	InitializeObjects();
	
	// Copying tiles from charblock 0 to charblock 4
	CopyTile(13, 0, 0, 4); // Player Idle Tile is 13
	
	CopyTile(29, 0, 1, 4);  // Walk Tile 1 is 29
	CopyTile(30, 0, 2, 4);  // Walk Tile 2 is 30
	
	CopyTile(21, 0, 3, 4);  // Hacking 1 is 21
	CopyTile(22, 0, 4, 4);  // Hacking 2 is 21
	
	CopyTile(35, 0, 5, 4);  // Death  is 35...
	CopyTile(36, 0, 6, 4);
	CopyTile(37, 0, 7, 4);
	CopyTile(38, 0, 8, 4);  // ... until 38
	
	CopyTile(14, 0, 9, 4); // Looking up is 14
	CopyTile(15, 0,10, 4); // Looking down/crouching is 15
	
	
	// Create Player object
	thePlayer = new Player(32, 32, 6, 7, 0);
	
	// Set up Maximum Speed
	thePlayer->MaxVelocity.X = (double)0.7;
	thePlayer->MaxVelocity.Y = 6;
	
	
	// Set up shadows for Level
	GenerateShadowMap();

	

}

void Game_Input()
{
	//Pushing start will push the Game state onto the stack, starting the game.
	key_poll();
	
	if(key_hit(KEY_START))
	{
		//Push Pause State WITHOUT offloading this state - preserves images etc.
		State nextState;
		nextState.StatePointer = Pause;
		g_StateStack->states.push(nextState);
	}
	
		
	if(key_is_down(KEY_LEFT))
	{
		thePlayer->Acceleration.X = -0.1;
		thePlayer->currentAnimation = thePlayer->runAnim;
		thePlayer->runAnim->Flipped = true;
		thePlayer->lookupAnim->Flipped = true;
		thePlayer->lookdownAnim->Flipped = true;
		thePlayer->idleAnim->Flipped = true;
		thePlayer->hackAnim->Flipped = true;
		thePlayer->deathAnim->Flipped = true;
	}
	else if(key_is_down(KEY_RIGHT))
	{
		thePlayer->Acceleration.X = 0.1;
		thePlayer->currentAnimation = thePlayer->runAnim;
		thePlayer->runAnim->Flipped = false;
		thePlayer->idleAnim->Flipped = false;
		thePlayer->hackAnim->Flipped = false;
		thePlayer->deathAnim->Flipped = false;		
		thePlayer->lookupAnim->Flipped = false;
		thePlayer->lookdownAnim->Flipped = false;
	}
	else
	{
		thePlayer->Acceleration.X = 0;
	}
	
	if(key_is_down(KEY_UP))
	{
		//Look up!
		thePlayer->currentAnimation = thePlayer->lookupAnim;
	}
	
	if(key_is_down(KEY_DOWN))
	{
		//Look down/crouch!
		thePlayer->currentAnimation = thePlayer->lookdownAnim;
		//Crouching in half-light makes us not visible:
		if(thePlayer->StealthState == 1)
		{
			thePlayer->StealthState = 2;
		}
		//But in reverse-slopes, it brings us into the light *more*
		if(thePlayer->StealthState == 3)
		{
			thePlayer->StealthState = 0;
		}
	}

	
	if(key_hit(KEY_A))
	{
		//Check to see if we can jump
		thePlayer->Velocity.Y = -4;
	}
	if(key_is_down(KEY_B))
	{
		thePlayer->currentAnimation = thePlayer->hackAnim;
	}
	if(key_hit(KEY_SELECT))
	{	
		//Death anim test
		thePlayer->currentAnimation = thePlayer->deathAnim;
	}
	
	// No Keys Pressed
	if(REG_KEYINPUT == KEY_MASK)
	{
		thePlayer->currentAnimation = thePlayer->idleAnim;
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
