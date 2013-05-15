#include "state_game.h"

bool gameHasInit = false;
unsigned short gameframeCounter = 0;
Player* thePlayer = 0;
//EyeBot* theEyeBot = 0;
Level* currentLevel = 0;

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
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
	// Set up backgrounds
	REG_BG3CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(1) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;	
	REG_BG0CNT = BG_CBB(2) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;	
	
	// Load Palette
	LoadPaletteBG(prototype_gfxPal, prototype_gfxPalLen);
	// Copy to Sprite Palette
	memcpy(pal_obj_mem, pal_bg_mem, prototype_gfxPalLen);
	
	// Load Game Tiles
	LoadIntoCharblock(0, 0, prototype_gfxTiles, prototype_gfxTilesLen);
	
	// Load Shadow Tiles
	LoadIntoCharblock(1, 0, shadowtiles_simpleTiles, shadowtiles_simpleTilesLen);
	
	// Load Eyebots & Vision Cones
	LoadIntoCharblock(4, 32, eyebotsTiles, eyebotsTilesLen);
	LoadIntoCharblock(4, 190, visionconeTiles, visionconeTilesLen);

	// Clear Screenblocks 
	CopyLevelToScreenblock(30, (u16**)Background); // Fill BG3 with Background (wallpaper) tiles
	CopyLevelToScreenblock(29, (u16**)Blank); // Filling the others with Blank tiles.
	CopyLevelToScreenblock(28, (u16**)Blank); // 
	CopyLevelToScreenblock(27, (u16**)Blank); // 
	

	//CopyLevelToScreenblock(28, (u16**)Level1);
	
	
	// Initialize Object Buffer
	InitializeObjects();
	
	// Copying player tiles from charblock 0 to charblock 4
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
	CopyTile(31, 0,11, 4); // Walljumping is 31
	
	
	// Create Player object
	thePlayer = new Player(32, 32, 6, 7, 1);
	//theEyeBot = new EyeBot(16, 16, 6, 6, 4, thePlayer);
	
	// Set up Maximum Speed
	
	thePlayer->MaxVelocity.X = 6;
	thePlayer->MaxVelocity.Y = 6;
	
	// Load Level 1 Layout into BG1
	
	
	// DEBUG: LEVEL 1 INFO
	Vector3D startLocation;
	startLocation.X = 32;
	startLocation.Y = 32;
	std::vector<Vector3D*> eyebots;
	Vector3D* eyebot1 = new Vector3D();
	eyebot1->X = 56;
	eyebot1->Y = 48;
	eyebots.push_back(eyebot1);
	Vector3D eyebotpt2;
	eyebotpt2.X = 56;
	eyebotpt2.Y = 16;
	std::vector<Vector3D> eyebot1path;
	eyebot1path.push_back(eyebotpt2);
	std::vector< std::vector<Vector3D> > eyebotPaths;
	eyebotPaths.push_back(eyebot1path);
	//// END OF DEBUG
	
	currentLevel = new Level((u16**)Level1, thePlayer, startLocation, eyebots, eyebotPaths, eyebotpt2);
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
		thePlayer->facingLeft = true;
	}
	else if(key_is_down(KEY_RIGHT))
	{
		thePlayer->Acceleration.X = 0.1;
		thePlayer->currentAnimation = thePlayer->runAnim;
		thePlayer->facingLeft = false;
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
	thePlayer->crouched = false;
	if(key_is_down(KEY_DOWN))
	{
		//Look down/crouch!
		thePlayer->currentAnimation = thePlayer->lookdownAnim;
		thePlayer->crouched = true;
	}

	
	if(key_hit(KEY_A))
	{
		//Check to see if we can jump
		if(thePlayer->CanJump)
		{
			thePlayer->Velocity.Y = -4;
		}
		else if(thePlayer->CanWallJump)
		{
			thePlayer->Velocity.Y = -4;
			if(thePlayer->facingLeft == true)
			{
				thePlayer->Velocity.X = 2;
			}
			else
			{
				thePlayer->Velocity.X = -2;
			}
		}
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
	currentLevel->UpdateAlertStatus();
	currentLevel->UpdateEnemies();
	//check win
}

void Game_Draw()
{
	//Game draw routines go here
	thePlayer->Draw();
	currentLevel->Draw();
	// Update Objects
	UpdateObjects();
}

void Game_Offload()
{
	// Clear stuff out, pop stack
}
