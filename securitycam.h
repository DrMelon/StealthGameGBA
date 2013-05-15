#pragma once

// Securitycam.h - Contains SecurityCamera class.

#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"
#include "player.h"
#include "gameobjects.h"

class SecurityCamera : public GameObject
{		
	public:
	
		typedef GameObject super; // Lets me use super() or super::Foo() for parent-class stuff.
		
		u16 AlertState; //Alert State: 0 = Not Suspicious, 1 = Suspicious, 2 = Alarmed
		u16 alertTime; // How many frames we're in suspicion mode.
		
		Animation* visionConeUp;
		Animation* visionConeSide;
		Animation* visionConeDown;
		
		Player* thePlayer; // Reference to the player, so they can find them etc.
		
		int direction; // 0 - Right, 1 - Down, 2 - Up, 3 - Down
		
		//Main Functions
		SecurityCamera(int x, int y, int width, int height, int objID, Player* _thePlayer);
		void CheckForPlayer();
		void Update();
		void Draw();

		
		
		
};

