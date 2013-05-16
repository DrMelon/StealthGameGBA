#include "eyebots.h"

EyeBot::EyeBot(int x, int y, int width, int height, int objID, Player* _thePlayer) : super(x, y, width, height, objID)
{
	eyeBotSide = new Animation(1, 1);
	eyeBotSide->Frames[0] = 16*2;
	eyeBotUp = new Animation(1, 1);
	eyeBotUp->Frames[0] = 17*2;
	eyeBotDown = new Animation(1, 1);
	eyeBotDown->Frames[0] = 18*2;
	
	
	
	currentAnimation = eyeBotSide;
	
	// Default Pattern of Movement is just sitting in-place.
	Vector3D p1;
	p1.X = x;
	p1.Y = y;
	pathPoints.push_back(p1);
	
	
	MaxVelocity.X = 5;
	MaxVelocity.Y = 5;
	
	thePlayer = _thePlayer;
	
	myCam = new SecurityCamera(x + width, y - 16, 64, 32, 128 - objID, thePlayer);
}

void EyeBot::Draw()
{
	// I dont use super::Draw() here because I need to override the main object drawing bit down there.


	//Convert world coordinates to screen coordinates - object needs to know scrolling offset.
	ScreenPositionX = (int)Position.X - ScrollX;
	ScreenPositionY = (int)Position.Y - ScrollY;
	
	if(Velocity.X > (double)0.1)
	{
		facingLeft = false;
	}
	else if(Velocity.X < (double)-0.1)
	{
		facingLeft = true;
	}

	
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
	
	// Check to see if we're on screen or not...
	if(ScreenPositionX < 0 || ScreenPositionX > 272 || ScreenPositionY < 0 || ScreenPositionY > 160)
	{
		SetObject(objectID, ATTR0_SHAPE(Shape) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_REG | ATTR0_Y(32),
                      ATTR1_SIZE(Size) | ATTR1_X(32),
                      ATTR2_ID(currentAnimation->Frames[currentAnimation->CurrentFrame]));
	}
	
	if(!facingLeft)
	{
		myCam->Position.X = Position.X + Width;
		myCam->Position.Y = Position.Y - (double)14;
	}
	else
	{
		myCam->Position.X = Position.X - (double)62;
		myCam->Position.Y = Position.Y - (double)12;
	}
	myCam->facingLeft = facingLeft;
	
	
	myCam->Draw();
}

void EyeBot::Update()
{
	myCam->ScrollX = ScrollX;
	myCam->ScrollY = ScrollY;
	myCam->Update();
	AlertState = myCam->AlertState;
	
	MoveToNextPoint();
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
	
	
	// There is no drag or level collision
	
	
	//Update Position using Velocity.
	Position = AddVectors2D(Position, Velocity);		
	
	// Update Animation & frameCounter
	currentAnimation->Update(frameCounter);
	frameCounter++;
	
	if(frameCounter > 60)
	{
		frameCounter = 0;
	}	
	
	// If we collide with the player, we kill him!
	if(Position.X + HalfWidth > thePlayer->Position.X && Position.Y + HalfWidth > thePlayer->Position.Y && Position.X + HalfWidth  < thePlayer->Position.X + thePlayer->Width && Position.Y + HalfWidth < thePlayer->Position.Y + thePlayer->Height)
	{
		thePlayer->Dead = true;
	}
	
	
	
}

void EyeBot::SwitchPoint()
{
	currentPoint++;
	if(currentPoint > pathPoints.size() - 1)
	{
		currentPoint = 0; // Go back to first point.
	}
	
	//Change direction depending on how far next point is relative to ourselves.
	Vector3D distanceToNextPoint;
	distanceToNextPoint.X = Position.X - pathPoints[currentPoint].X;
	distanceToNextPoint.Y = Position.Y - pathPoints[currentPoint].Y;
	// If
	if(fabs(distanceToNextPoint.Y) < fabs(distanceToNextPoint.X))
	{
		currentAnimation = eyeBotSide;
	}
	else
	{
		if(distanceToNextPoint.Y < (double)0)
		{
			currentAnimation = eyeBotUp;
			currentDirection = 2; // Up
		}
		else
		{
			currentAnimation = eyeBotDown;
			currentDirection = 3; // Down
		}
	}
	
	if(distanceToNextPoint.X > (double)0)
	{
		facingLeft = true;
		currentDirection = 1; // Left
	}
	else
	{
		facingLeft = false;
		currentDirection = 0; // Right
	}
	
	myCam->direction = currentDirection;
	
}

void EyeBot::MoveToNextPoint()
{

	Vector3D amountToMove;
	
	// How far are we from the target?
	amountToMove.X = Position.X - pathPoints[currentPoint].X;
	amountToMove.Y = Position.Y - pathPoints[currentPoint].Y;
	
	// If we're suspicious or alerted, we move towards the player to try and kill them.
	if(AlertState != 0)
	{
		amountToMove.X = Position.X - thePlayer->Position.X;
		amountToMove.Y = Position.Y - thePlayer->Position.Y;
		
	}
	
	// If we're really close, we made it.
	if(fabs(amountToMove.X) < (double)1 && fabs(amountToMove.Y) < (double)1)
	{
		SwitchPoint();
		return;
	}
	
	Normalize(amountToMove); // Convert to Unit Vector
	
	amountToMove = ScalarMult(amountToMove, (double)0.7);  // Slow it down a little.
	// Vector turns out to be reversed...
	amountToMove.X = -amountToMove.X;
	amountToMove.Y = -amountToMove.Y;
	Velocity.X = amountToMove.X;
	Velocity.Y = amountToMove.Y;
	

	
	return;
	
	
}