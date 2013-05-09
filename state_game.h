// Game game state - actual game logic goes in here.
#pragma once

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" 
#include "tonchelper.h"

// Master State List
#include "statelist.h"

// Objects
#include "player.h"
#include "securitycam.h"
#include "eyebots.h"

// Images Needed
#include "prototype_gfx.h"
#include "shadowtiles_simple.h"
#include "visioncone.h"
#include "gfx_eyebots.h"


// Levels
#include "levels.h"

void Game_Init();
void Game_Input();
void Game_Update();
void Game_Draw();
void Game_Offload();

