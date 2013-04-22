#pragma once

// Player.h - Contains Player class and useful stuff for them, like animations.

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
		bool	Flipped; // Flip Horizontally?
		
		inline Animation(u16 _numFrames, u16 _frameDelay)
		{
			Frames = new u16[_numFrames];
			FrameDelay = _frameDelay;
			CurrentFrame = 0;
			NumFrames = _numFrames;
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
						CurrentFrame = 0;
					}
				}
			} 
		}
};

class Player
{
	private:

		
		bool facingLeft;
		
		// These are used to track the player's position on-screen. Can be useful for scrolling etc.
		int ScreenPositionX;
		int ScreenPositionY;
		int ScrollX;
		int ScrollY;
		
		// Pointer to current map
		u16** currentMap;
		

		
		u16 frameCounter; // For animations
		
	public:
		// Vectors are useful for movement/collision stuff.
		Vector3D Position;
		Vector3D Velocity;
		Vector3D MaxVelocity;	
		Vector3D Acceleration;
		
		// List of animations
		Animation* currentAnimation;
		Animation* idleAnim;
		Animation* runAnim;
		Animation* hackAnim;
		Animation* lookupAnim;
		Animation* lookdownAnim;	
		Animation* deathAnim;
		
		double Drag;
		double Width;
		double Height;
	
	
	
		//Main Functions
		Player(int x, int y, u16** _currentMap);
		void Update();
		void Draw();
		
		//Mutator Functions
		
		
		//Helper Functions (like collision checking)
		void CheckCollision(); // Collision Functions
		u16 GetMapTileAt(int x, int y); // Gets a map tile given a world coordinate.
		
		
		
};

