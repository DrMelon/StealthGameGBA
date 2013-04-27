#include "gameobjects.h"

GameObject::GameObject(int x, int y, int width, int height, int objID)
{
	objectID = objID;
	
	Position.X = x;
	Position.Y = y;
	Position.Z = 0;
	
	Velocity.X = 0;
	Velocity.Y = 0;
	
	Shape = 0;
	Size = 0;
	
	Width = width;
	HalfWidth = Width / (double)2;
	Height = height;
	
	Acceleration.X = 0;
	Acceleration.Y = 0;
	
	Drag = 0.3;
	
	ScrollX = 0;
	ScrollY = 0;
	
	frameCounter = 0;
	
	// Default Blank Animation
	currentAnimation = new Animation(1, 1);
	currentAnimation->Frames[0] = 128;
	
	
	
		
	Draw();
}

void GameObject::Draw()
{
	//Convert world coordinates to screen coordinates - object needs to know scrolling offset.
	ScreenPositionX = (int)Position.X - ScrollX;
	ScreenPositionY = (int)Position.Y - ScrollY;
	
	// Objects are given an ID on spawning - all objects are spawned through an object creator.
	// The object creator won't allow an ID greater of 128.
	if(facingLeft == true)
	{
		SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(ScreenPositionY),
				  ATTR1_SIZE(Size) | ATTR1_X(ScreenPositionX) | ATTR1_HFLIP,
				  ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	else
	{
	SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(ScreenPositionY),
                      ATTR1_SIZE(Size) | ATTR1_X(ScreenPositionX),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}

}

void GameObject::Update()
{

	//Update Velocity using Acceleration.
	Velocity = AddVectors2D(Velocity, Acceleration);	
	
	//Clip Velocity to Max Velocity
	if(Velocity.X < -MaxVelocity.X)
	{
		Velocity.X = -MaxVelocity.X;
	}
	if(Velocity.X > MaxVelocity.X)
	{
		Velocity.X = MaxVelocity.X;
	}
	if(Velocity.Y < -MaxVelocity.Y)
	{
		Velocity.Y = -MaxVelocity.Y;
	}
	if(Velocity.Y > MaxVelocity.Y)
	{
		Velocity.Y = MaxVelocity.Y;
	}
	
	
	if(fabs(Acceleration.X) < (double)0.1f) // If there is no force being applied, drag will slow us down.
	{
		Velocity.X *= Drag; 
	}
	
	// Check for collisions before updating position with velocity.
	// CheckCollision will alter the velocity to prevent a collision before it happens. 
	CheckCollision();
	
	//Update Position using Velocity.
	Position = AddVectors2D(Position, Velocity);		
	
	// Update Animation & frameCounter
	currentAnimation->Update(frameCounter);
	frameCounter++;
	
	if(frameCounter > 60)
	{
		frameCounter = 0;
	}

	
}

u16 GameObject::GetMapTileAt(int x, int y, int screenblock = 28)
{
	// Retrieve map tile on current level at this world coordinate.
	
	int TileX, TileY;
	
	// Tiles are 8x8, so world -> tile is just a division by 8
	
	TileX = x / 8;
	TileY = y / 8;
	
	// Tilemap is 32x32, so we add the X-coordinate multiplied by 32 to get the right place in memory.
	return se_mem[screenblock][TileX + (TileY*32)];
	
	
	
}

void GameObject::CheckCollision()
{

	// Have to check X and Y axes separately to prevent "stickiness"
	
	if(GetMapTileAt(Position.X + Velocity.X, Position.Y + Height) != 7 || GetMapTileAt(Position.X + Velocity.X, Position.Y) != 7 || GetMapTileAt(Position.X + Velocity.X + Width, Position.Y) != 7 || GetMapTileAt(Position.X + Velocity.X + Width, Position.Y + Height) != 7 ) // Have to check all 4 corners for X axis
	{																																						
		Velocity.X = 0;																																		
	}                                                                                                                                                       
	
	if(GetMapTileAt(Position.X, Position.Y + Velocity.Y + Height) != 7 || GetMapTileAt(Position.X + Width, Position.Y + Velocity.Y) != 7 || GetMapTileAt(Position.X, Position.Y + Velocity.Y) != 7 || GetMapTileAt(Position.X + Width, Position.Y + Velocity.Y + Height) != 7 ) // Have to check all 4 corners for Y axis
	{
		Velocity.Y = 0;
	}

}
