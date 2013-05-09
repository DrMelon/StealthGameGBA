#include "eyebots.h"

EyeBot::EyeBot(int x, int y, int width, int height, int objID) : super(x, y, width, height, objID)
{
	eyeBotSide = new Animation(1, 1);
	eyeBotSide->Frames[0] = 16*2;
	eyeBotUp = new Animation(1, 1);
	eyeBotUp->Frames[0] = 17*2;
	eyeBotDown = new Animation(1, 1);
	eyeBotDown->Frames[0] = 18*2;
	
	currentAnimation = eyeBotSide;
	
	// Default Pattern of Movement
	Vector3D p1;
	p1.X = 16;
	p1.Y = 16;
	Vector3D p2;
	p2.X = 64;
	p2.Y = 16;
	Vector3D p3;
	p3.X = 64;
	p3.Y = 64;
	Vector3D p4;
	p4.X = 16;
	p4.Y = 64;
	pathPoints.push_back(p1);
	pathPoints.push_back(p2);
	pathPoints.push_back(p3);
	pathPoints.push_back(p4);
	
	MaxVelocity.X = 5;
	MaxVelocity.Y = 5;
	
	myCam = new SecurityCamera(x + width, y - 16, 64, 32, 128 - objID);
}

void EyeBot::Draw()
{
	// I dont use super::Draw() here because I need to override the main object drawing bit down there.


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
	
	myCam->Draw();
}

void EyeBot::Update()
{
	myCam->Update();
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
	
	
	// There is no drag or collision
	
	
	//Update Position using Velocity.
	Position = AddVectors2D(Position, Velocity);		
	
	// Update Animation & frameCounter
	currentAnimation->Update(frameCounter);
	frameCounter++;
	
	if(frameCounter > 60)
	{
		frameCounter = 0;
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
		}
		else
		{
			currentAnimation = eyeBotDown;
		}
	}
	
	if(distanceToNextPoint.X > (double)0)
	{
		facingLeft = true;
	}
	else
	{
		facingLeft = false;
	}
	
}

void EyeBot::MoveToNextPoint()
{

	Vector3D amountToMove;
	
	// How far are we from the target?
	amountToMove.X = Position.X - pathPoints[currentPoint].X;
	amountToMove.Y = Position.Y - pathPoints[currentPoint].Y;
	
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