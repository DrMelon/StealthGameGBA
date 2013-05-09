#include "securitycam.h"

SecurityCamera::SecurityCamera(int x, int y, int width, int height, int objID) : super(x, y, width, height, objID)
{
	//The security camera object is actually just its view-cone!
	// The camera itself is just on the map.
	visionCone = new Animation(1, 1);
	visionCone->Frames[0] = 95*2;
	
	//Security Camera VisionCones are 64x32: 1x3 on the GBA's Object Size Map
	Shape = 1;
	Size = 3;
	
	currentAnimation = visionCone;
	
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
}

void SecurityCamera::Update()
{
	super::Update();
	
	// Watch for Player


	
}
