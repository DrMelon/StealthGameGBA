#pragma once

// Securitycam.h - Contains SecurityCamera class.

#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"
#include "gameobjects.h"

class SecurityCamera : public GameObject
{		
	public:
	
		typedef GameObject super; // Lets me use super() or super::Foo() for parent-class stuff.
		
		u16 AlertState; //Alert State: 0 = Not Suspicious, 1 = Suspicious, 2 = Alarmed
		
		Animation* visionCone;
		
		//Main Functions
		SecurityCamera(int x, int y, int width, int height, int objID);
		void Update();
		void Draw();

		
		
		
};

