#pragma once

#include "gameobjects.h"

class Disk : public GameObject // the data disk, our main objective!
{		
	public:
	
		typedef GameObject super; // Lets me use super() or super::Foo() for parent-class stuff.
		
		Animation* diskAnim;
		
		//Main Functions
		Disk(int x, int y, int width, int height, int objID);
		void Update();
		void Draw();

		
		
		
};