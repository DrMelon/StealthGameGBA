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
		
		Animation* eyeBotUp;
		Animation* eyeBotSide;
		Animation* eyeBotDown;

		
		//Main Functions
		EyeBot(int x, int y, int width, int height, int objID);
		void MoveToNextPoint();
		void SwitchPoint();
		void Update();
		void Draw();

		
		
		
};