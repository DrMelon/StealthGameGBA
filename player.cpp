#include "player.h"

Player::Player(int x, int y, u16** _currentMap)
{
	Position.X = x;
	Position.Y = y;
	Position.Z = 0;
	
	Velocity.X = 0;
	Velocity.Y = 0;
	
	Width = 7;
	Height = 7;
	
	Acceleration.X = 0;
	Acceleration.Y = 0.245f; // Gravity
	
	Drag = 0.3;
	
	ScrollX = 0;
	ScrollY = 0;
	
	frameCounter = 0;
	
	// Set up animations - because TONC sees tile references in 4bpp mode, i need to multiply the tile index by 2 each time.
	idleAnim = new Animation(1,1);
	idleAnim->Frames[0] = 0;
	
	runAnim = new Animation(2,15);
	runAnim->Frames[0] = 1*2;
	runAnim->Frames[1] = 2*2;
	
	hackAnim = new Animation(2,5);
	hackAnim->Frames[0] = 3*2;
	hackAnim->Frames[1] = 4*2;

	
	deathAnim = new Animation(4,15);
	deathAnim->Frames[0] = 5*2;
	deathAnim->Frames[1] = 6*2;
	deathAnim->Frames[2] = 7*2;
	deathAnim->Frames[3] = 8*2;
	
	currentAnimation = idleAnim;
	
	
	
	Draw();
}

void Player::Draw()
{
	// Animation Properties would go here.
	
	//Convert world coordinates to screen coordinates - player needs to know scrolling offset.
	ScreenPositionX = (int)Position.X - ScrollX;
	ScreenPositionY = (int)Position.Y - ScrollY;
	

	
	
	// Player Object is always object 0
	if(currentAnimation->Flipped == true)
	{
		SetObject(0, ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(ScreenPositionY),
				  ATTR1_SIZE(0) | ATTR1_X(ScreenPositionX) | ATTR1_HFLIP,
				  ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	else
	{
	SetObject(0, ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(ScreenPositionY),
                      ATTR1_SIZE(0) | ATTR1_X(ScreenPositionX),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}

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
	
	//Update Scrolling from Position.
	
	if(((int)Position.X - ScrollX) > SCREEN_WIDTH - 16)
	{
		ScrollX++;
	}
	else if(((int)Position.X - ScrollX) < 16 && ScrollX > 0)
	{
		ScrollX--;
	}
	
	if(((int)Position.Y - ScrollY) > SCREEN_HEIGHT - 16)
	{
		ScrollY++;
	}
	else if(((int)Position.Y - ScrollY) < 16 && ScrollY > 0)
	{
		ScrollY--;
	}
	
	REG_BG1HOFS = ScrollX;
	REG_BG2HOFS = ScrollX;
	REG_BG3HOFS = ScrollX;
	REG_BG1VOFS = ScrollY;
	REG_BG2VOFS = ScrollY;
	REG_BG3VOFS = ScrollY;
	
	
	// Update Animation & frameCounter
	currentAnimation->Update(frameCounter);
	frameCounter++;
	
	if(frameCounter > 60)
	{
		frameCounter = 0;
	}

	
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
	
	return se_mem[28][TileX + (TileY*32)];
	
	
	
}

void Player::CheckCollision()
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
