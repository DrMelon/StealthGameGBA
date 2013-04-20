// Game game state - actual game logic goes in here.
#pragma once

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" 
#include "tonchelper.h"

// Master State List
#include "statelist.h"

// Players
#include "player.h"

// Images Needed
#include "prototype_gfx.h"

// Levels
#include "levels.h"

void Game_Init();
void Game_Input();
void Game_Update();
void Game_Draw();
void Game_Offload();

