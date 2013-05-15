#pragma once

#include "gameobjects.h"
#include "securitycam.h"
#include <vector>

class EyeBot : public GameObject
{		
	public:
	
		typedef GameObject super; // Lets me use super() or super::Foo() for parent-class stuff.
		std::vector<Vector3D> pathPoints; // Points on path to follow.
		int currentPoint;
		int currentDirection; // Current Direction:  0 - Right, 1 - Left, 2 - Up, 3 - Down
		
		u16 AlertState; //Alert State: 0 = Not Suspicious, 1 = Suspicious, 2 = Alarmed
		u16 alertTime; // How long it takes for an eyebot to go from suspicious back to not suspicious.
		
		Animation* eyeBotUp;
		Animation* eyeBotSide;
		Animation* eyeBotDown;
	
		SecurityCamera* myCam; // Eyebot's view.
		Player* thePlayer; // The player
		
		//Main Functions
		EyeBot(int x, int y, int width, int height, int objID, Player* _thePlayer);
		void MoveToNextPoint();
		void SwitchPoint();
		void Update();
		void Draw();

		
		
		
};