#include "player.h"

Player::Player(int x, int y, u16** _currentMap)
{
	Position.X = x;
	Position.Y = y;
	Position.Z = 0;
	
	Velocity.X = 0;
	Velocity.Y = 0;
	
	Width = 8;
	Height = 8;
	
	Acceleration.X = 0;
	Acceleration.Y = 0.245f; // Gravity
	
	Drag = 0.3;
	
	ScrollX = 0;
	ScrollY = 0;
	
	
	Draw();
}

void Player::Draw()
{
	// Animation Properties would go here.
	
	//Convert world coordinates to screen coordinates - player needs to know scrolling offset.
	ScreenPositionX = (int)Position.X - ScrollX;
	ScreenPositionY = (int)Position.Y - ScrollY;
	
	
	// Player Object is always object 0
	SetObject(0, ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(ScreenPositionY),
                      ATTR1_SIZE(0) | ATTR1_X(ScreenPositionX),
                      ATTR2_ID(0));
}

void Player::Update()
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
	
	
	

	
}

u16 Player::GetMapTileAt(int x, int y)
{
	// Retrieve map tile on current level at this world coordinate.
	
	int TileX, TileY;
	
	// Tiles are 8x8, so world -> tile is just a division by 8
	
	TileX = x / 8;
	TileY = y / 8;
	
	// Tilemap is 32x32, so we add the X-coordinate multiplied by 32 to get the right place in memory.
	
	// Colour the tile DEBUG
	//se_mem[29][TileX + (TileY*32)] = 20;
	
	return se_mem[29][TileX + (TileY*32)];
	
	
	
}

void Player::CheckCollision()
{

	// Have to check X and Y axes separately to prevent "stickiness"
	
	if(GetMapTileAt(Position.X + Velocity.X, Position.Y) != 7 || GetMapTileAt(Position.X + Velocity.X + Width, Position.Y) != 7 ) // Left and Right Sides
	{
		Velocity.X = 0;
	}
	
	if(GetMapTileAt(Position.X, Position.Y + Velocity.Y + Height) != 7 || GetMapTileAt(Position.X, Position.Y + Velocity.Y) != 7 ) // Top and Bottom Sides
	{
		Velocity.Y = 0;
	}
/*
	if(GetMapTileAt(Position.X + Velocity.X, Position.Y + Velocity.Y) != 7)
	{
		//If this is a solid tile, we want to clip the velocity to the distance from us to the tile.
		
		// Get the distance from us to the next tile:
		Vector3D DistToTile;
		DistToTile.X = ((int)(Position.X + Velocity.X) / 8);
		DistToTile.X -= Position.X;
		DistToTile.Y = ((int)(Position.Y + Velocity.Y) / 8);
		DistToTile.Y -= Position.Y;
		
		// Set the velocity (distance to be covered in this frame) to the distance between us and the tile, effectively making us run into it and stop short.
	//	Velocity.X = DistToTile.X;
	//	Velocity.Y = DistToTile.Y;
	
		Velocity.X = 0;
		Velocity.Y = 0;
		
	}
	*/
}
