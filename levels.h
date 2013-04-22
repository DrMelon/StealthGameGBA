#pragma once

// Levels.h - Contains level layouts and information about the tileset.
#include "tonclib/include/tonc.h" 

#include <string.h>

// Tileset Info

// 0 - 2   Walls, Top Edge
// 3 - 4   Wallpaper Tiles
// 5 	   Unhacked Terminal
// 6	   Hacked Terminal
// 7 	   <BLANK>
// 8 - 10  Walls, Middle
// 11      Door Top, Clean
// 12	   Door Top, Bloody
// 13      Player Idle Sprite
// 14      Player Looking Up
// 15      Player Crouching
// 16 - 18 Walls, Bottom Edge
// 19      Door Bottom, Clean
// 20      Door Bottom, Bloody
// 21 - 22 Player Hacking Terminal
// 23      <BLANK>
// 24 - 26 Walls, Single Tile, Horizontal
// 27 - 28 Security Cameras, Left and Right
// 29 - 30 Player Walking
// 31      <BLANK>
// 32 - 34 Walls, Single Tile, Vertical
// 35 - 38 Player Death Animation
// 39	   <BLANK>
// 40 - 47 Walls, Inner Corners
// 48 - 51 Walls, Single Tile, Corners

extern const u16 Blank[32][32];
extern const u16 Background[32][32];
extern const u16 Level1[32][32];
extern const u16 Level2[32][32];
extern const u16 Level3[32][32];

void GenerateShadowMap(u16** Level);
