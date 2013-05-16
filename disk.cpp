#include "disk.h"

Disk::Disk(int x, int y, int width, int height, int objID) : super(x, y, width, height, objID)
{
	diskAnim = new Animation(1, 1);
	diskAnim->Frames[0] = 12*2;

	currentAnimation = diskAnim;

}

void Disk::Draw()
{
	super::Draw();
	
	// Check to make sure we haven't gone offscreen:
		
	// Check to see if we're on screen or not...
	if(ScreenPositionX < 0 || ScreenPositionX > 248 || ScreenPositionY < 0 || ScreenPositionY > 160)
	{
		SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_REG | ATTR0_Y(32),
                      ATTR1_SIZE(Size) | ATTR1_X(32),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	
}

void Disk::Update()
{
	//nada
}
