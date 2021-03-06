#pragma once

// Gameobjects.h - Generalized game object class & animation class

#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"

class Animation
{
	public:
		u16*	Frames; // Actual frames
		u16		NumFrames; // Max is 32
		u16		FrameDelay; // Delay in game frames between each frame changing
		u16		CurrentFrame; // Frame being shown right now
		bool	Flipped; // Flip Horizontally
		bool	Loop;	// Does the animation loop back to the start?
		
		inline Animation(u16 _numFrames, u16 _frameDelay)
		{
			Frames = new u16[_numFrames];
			FrameDelay = _frameDelay;
			CurrentFrame = 0;
			NumFrames = _numFrames;
			Loop = true; // Loop by default
		}
		
		inline void Update(u16 frameCounter)
		{
			if(NumFrames > 1) // no point doin useless stuff if we have a single frame animation
			{
				if((frameCounter % FrameDelay) == 0)
				{
					CurrentFrame++;
					if(CurrentFrame >= NumFrames)
					{
						if(Loop)
						{
							CurrentFrame = 0;
						}
						else
						{
							CurrentFrame = NumFrames - 1;
						}
					}
				}
			} 
		}
};

class GameObject
{


		
	public:
		// Pointer to current map
		u16** currentMap;
						
		u16 frameCounter; // For animations	
		int objectID; // For Object Managing Purposes
		// Vectors are useful for movement/collision stuff.
		Vector3D Position;
		Vector3D Velocity;
		Vector3D MaxVelocity;	
		Vector3D Acceleration;
				
		double Drag;
		double Width;
		double Height;
		double HalfWidth;
		
		int Shape;
		int Size;
		
		// These are used to track the object's position on-screen. Can be useful for scrolling etc.
		int ScreenPositionX;
		int ScreenPositionY;
		int ScrollX;
		int ScrollY;
		
		//Animation holder
		Animation* currentAnimation;
		bool facingLeft;
	
		//Main Functions
		GameObject(int x, int y, int width, int height, int objID);
		void Update();
		void Draw();	
		
		//Helper Functions (like collision checking)
		void CheckCollision(); // Basic Map Collsion
		// TODO- Object-On-Object Collisions
		u16 GetMapTileAt(int x, int y, int screenblock); // Gets a map tile at the given world coordinate.
				
		
};

