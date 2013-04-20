#pragma once

// Player.h - Contains Player class and useful stuff for them, like animations.

#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"

class Player
{
	private:

		
		bool facingLeft;
		
		// These are used to track the player's position on-screen. Can be useful for scrolling etc.
		int ScreenPositionX;
		int ScreenPositionY;
		int ScrollX;
		int ScrollY;
		
		// Pointer to current map
		u16** currentMap;
		
		
		
	public:
		// Vectors are useful for movement/collision stuff.
		Vector3D Position;
		Vector3D Velocity;
		Vector3D MaxVelocity;	
		Vector3D Acceleration;
		
		double Drag;
		double Width;
		double Height;
	
	
	
		//Main Functions
		Player(int x, int y, u16** _currentMap);
		void Update();
		void Draw();
		
		//Mutator Functions
		
		
		//Helper Functions (like collision checking)
		void CheckCollision(); // Collision Functions
		u16 GetMapTileAt(int x, int y); // Gets a map tile given a world coordinate.
		
		
		
};

