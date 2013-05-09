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
	p1.X = 32;
	p1.Y = 16;
	Vector3D p2;
	p2.X = 64;
	p2.Y = 16;
	pathPoints.push_back(p1);
	pathPoints.push_back(p2);
	
	MaxVelocity.X = 5;
	MaxVelocity.Y = 5;
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

void EyeBot::Update()
{
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
		if(distanceToNextPoint.Y > (double)0)
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
	
	amountToMove = ScalarMult(amountToMove, (double)0.7); 
	// Vector turns out to be reversed...
	amountToMove.X = -amountToMove.X;
	amountToMove.Y = -amountToMove.Y;
	Drag = 1;
	Velocity.X = amountToMove.X;
	Velocity.Y = amountToMove.Y;
	

	
	return;
	
	
}