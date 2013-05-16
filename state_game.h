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

#include "status_bad.h"
#include "status_good.h"
#include "status_dead.h"
#include "status_seen.h"

// Levels
#include "level_data.h"
#include "levels.h"

void Game_Init();
void Game_Input();
void Game_Update();
void Game_Draw();
void Game_Offload();
void Draw_Status_Indicator();

