// Game game state - actual game logic goes in here.
#pragma once

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "level_data.h"

// Master State List
#include "statelist.h"

// Graphics
#include "pausestuff.h"


void Pause_Init();
void Pause_Input();
void Pause_Update();
void Pause_Draw();
void Pause_Offload();

