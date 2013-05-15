#include "player.h"

Player::Player(int x, int y, int width, int height, int objID) : super(x, y, width, height, objID)
{
	Acceleration.Y = 0.245f; // Gravity

	// Set up animations - because TONC sees object tile references in 4bpp mode, i need to multiply the tile index by 2 each time.
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
	deathAnim->Loop = false;
	
	lookupAnim = new Animation(1,1);
	lookupAnim->Frames[0] = 9*2;
	
	lookdownAnim = new Animation(1,1);
	lookdownAnim->Frames[0] = 10*2;
	
	wallJumpAnim = new Animation(1,1);
	wallJumpAnim->Frames[0] = 11*2;
	
	currentAnimation = idleAnim;

	Draw();
}

void Player::Draw()
{
	
	
	// Change skin tone (palette entries 20 and 23) and goggle colour (17) depending on shadow level
	switch(StealthState)
	{
		case 0:
			// Fully Visible:
			pal_obj_mem[20] = RGB15(29, 23, 15);
			pal_obj_mem[23] = RGB15(31, 25, 14);
			pal_obj_mem[17] = RGB15(31, 0, 0);
			break;
		case 1:
			// Half-Visible:
			pal_obj_mem[20] = RGB15(20, 16, 13);
			pal_obj_mem[23] = RGB15(21, 18, 14);
			pal_obj_mem[17] = RGB15(31, 31, 0);	
			break;
		case 2:
			// Not Visible:
			pal_obj_mem[20] = RGB15(12, 9, 9);
			pal_obj_mem[23] = RGB15(12,10,10);
			pal_obj_mem[17] = RGB15(2, 31, 0);	
			break;
		case 3:
			// Half-Visible again
			pal_obj_mem[20] = RGB15(20, 16, 13);
			pal_obj_mem[23] = RGB15(21, 18, 14);
			pal_obj_mem[17] = RGB15(31, 31, 0);	
			break;
			
			
	}
	
	super::Draw();

}

void Player::Update()
{
	super::Update();
	CheckCollision();
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
	
	
	// Change stealth state depending on area visiblity.
	StealthState = GetMapTileAt(Position.X+HalfWidth, Position.Y, 29);
	if(crouched)
	{
		//Crouching in half-light makes us not visible:
		if(StealthState == 1)
		{
			StealthState = 2;
		}
		//But in reverse-slopes, it brings us into the light *more*
		if(StealthState == 3)
		{
			StealthState = 0;
		}
	}
	

	
}

u16 Player::GetMapTileAt(int x, int y, int screenblock = 28)
{
	return super::GetMapTileAt(x, y, screenblock);
}

void Player::CheckCollision()
{
	CanJump = false;
	CanWallJump = false;
	// If we're on the ground, we can jump.
	if(GetMapTileAt(Position.X+HalfWidth, Position.Y+Height+(double)8, 28) != TILE_EMPTY)
	{
		CanJump = true;
		MaxVelocity.X = (double)0.7;
		Drag = (double)0.3;
	}
	else
	{
		//Higher airspeed
		MaxVelocity.X = 6;
		Drag = (double)1; //reducing air friction too
		// If we're touching a wall, we can walljump.
		if(GetMapTileAt(Position.X - Velocity.X - (double)1, Position.Y, 28) != TILE_EMPTY || GetMapTileAt(Position.X + Width + Velocity.X + double(1), 28) != TILE_EMPTY)
		{
			CanWallJump = true;
			currentAnimation = wallJumpAnim;
		}
	}
	

	super::CheckCollision();	
}
