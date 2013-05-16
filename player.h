#pragma once

// Player.h - Contains Player class and useful stuff for them, like animations.

#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"
#include "gameobjects.h"

class Player : public GameObject
{		
	public:
	
		typedef GameObject super; // Lets me use super() or super::Foo() for parent-class stuff.
		bool CanJump;
		bool CanWallJump;
		bool crouched;
		bool Dead;
		u16 StealthState; //Stealth State: 0 = Fully Visible, 1 = Semi-Hidden, 2 = Fully Hidden, 3 = Semi-Hidden again
	
		// Used animations
		Animation* idleAnim;
		Animation* runAnim;
		Animation* hackAnim;
		Animation* lookupAnim;
		Animation* lookdownAnim;	
		Animation* deathAnim;
		Animation* wallJumpAnim;
	
		//Main Functions
		Player(int x, int y, int width, int height, int objID);
		void Update();
		void Draw();
		//Helper Functions (like collision checking)
		void CheckCollision(); // Collision Functions
		u16 GetMapTileAt(int x, int y, int screenblock); // Gets a map tile given a world coordinate.
		
		
		
};

