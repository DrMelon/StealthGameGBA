
// Menu game state - basically has a title screen with "PUSH START" on it. Yay!
#pragma once

#include <string.h>
#include <stdlib.h>
#include "tonclib/include/tonc.h" 

// Images Needed
#include "title_screen.h"

void Menu();

void Menu_Init();
void Menu_Input();
void Menu_Update();
void Menu_Draw();
void Menu_Offload();