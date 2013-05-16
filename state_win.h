
// Menu game state - basically has a title screen with "PUSH START" on it. Yay!
#pragma once

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" 

// Master State List
#include "statelist.h"

// Images Needed
#include "business.h"

void Win_Init();
void Win_Input();
void Win_Update();
void Win_Draw();
void Win_Offload();

