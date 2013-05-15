#include "securitycam.h"

SecurityCamera::SecurityCamera(int x, int y, int width, int height, int objID, Player* _thePlayer) : super(x, y, width, height, objID)
{
	//The security camera object is actually just its view-cone!
	// The camera itself is just on the map.
	visionConeSide = new Animation(1, 1);
	visionConeSide->Frames[0] = 95*2;
	visionConeUp = new Animation(1, 1);
	visionConeUp->Frames[0] = 95*2;	
	visionConeDown = new Animation(1, 1);
	visionConeDown->Frames[0] = 25*2;	
	
	thePlayer = _thePlayer;
	
	alertTime = 0;
	
	//Security Camera VisionCones are 64x32: 1x3 on the GBA's Object Size Map
	Shape = 1;
	Size = 3;
	
	currentAnimation = visionConeSide;
	
	// NOTE: This initializes Alpha Blending on the GBA:
	REG_BLDCNT = BLD_BUILD(
		BLD_OBJ, // Top Layers
		BLD_BG1 | BLD_BG2 | BLD_BG3, // Bottom Layers
		BLD_STD); // Standard blending mode

	
	BFN_SET(REG_BLDCNT, BLD_STD, BLD_MODE);
	// 50/50 Blend
	
	REG_BLDALPHA = BLDA_BUILD(15,7);
		
	Draw();
}

void SecurityCamera::Draw()
{
	// I dont use super::Draw() here because I need to override the main object drawing bit down there.


	//Convert world coordinates to screen coordinates - object needs to know scrolling offset.
	ScreenPositionX = (int)Position.X - ScrollX;
	ScreenPositionY = (int)Position.Y - ScrollY;
	
	

	
	// Objects are given an ID on spawning - all objects are spawned through an object creator.
	// The object creator won't allow an ID greater of 128.
	if(facingLeft == true)
	{
		SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_BLEND | ATTR0_Y(ScreenPositionY),
				  ATTR1_SIZE(Size) | ATTR1_X(ScreenPositionX) | ATTR1_HFLIP,
				  ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	else
	{
	SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_BLEND | ATTR0_Y(ScreenPositionY),
                      ATTR1_SIZE(Size) | ATTR1_X(ScreenPositionX),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	
	if(direction == 3 || direction == 2)
	{
		//Facing down/up, size and shape swapped.
		SetObject(objectID, ATTR0_SHAPE(Size) | ATTR0_8BPP | ATTR0_REG | ATTR0_BLEND | ATTR0_Y(ScreenPositionY),
				  ATTR1_SIZE(Shape) | ATTR1_X(ScreenPositionX) | ATTR1_HFLIP,
				  ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	
	// Don't go off-screen!
	if(ScreenPositionX < -63 || ScreenPositionX > 272 || ScreenPositionY < 0 || ScreenPositionY > 160)
	{
		SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_REG | ATTR0_Y(32),
                      ATTR1_SIZE(Size) | ATTR1_X(32),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
		
}

void SecurityCamera::Update()
{
	CheckForPlayer();
	super::Update();
	

}


void SecurityCamera::CheckForPlayer()
{
	// Checking 4 tiles in a straight line ahead, with a couple extra for the edges of the cone.
	for(int i = 0; i < 4; i++)
	{
		// If we've hit solid ground or full shadow, we should do nothing.
		if(thePlayer->StealthState == 2)
		{
			break;
		}
		else
		{
			//Check for player at this position.
			if(Position.X + (double)(i*8) > thePlayer->Position.X && Position.Y + Height/(double)2 > thePlayer->Position.Y && Position.X + (double)(i*8) < thePlayer->Position.X + thePlayer->Width && Position.Y + Height/(double)2 < thePlayer->Position.Y + thePlayer->Height)
			{
				
				// In half-shadow, we simply become suspicious.
				if(thePlayer->StealthState == 1 || thePlayer->StealthState == 3)
				{
					AlertState = 1;
					alertTime = 120;
				}
				else
				{
					AlertState = 2;
				}
				return;
			}
		}
	}
	
	if(alertTime > 0)
	{
		alertTime--;
	}
	if(alertTime == 0 && AlertState == 1)
	{
		AlertState = 0;
	}
	
}


