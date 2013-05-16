#pragma once

// Levels.h - Contains level layouts and information about the tileset.
#include "tonclib/include/tonc.h" 
#include "tonchelper.h"
#include "vectormath.h"
#include "eyebots.h"
#include "disk.h"
#include <string.h>
#include <algorithm>
#include <vector>

class Level
{
	// This class keeps information about the current level.
	public:
		u16 alertStatus; // Are enemies alerted?
		
		std::vector<EyeBot*> eyebotInstances; // The actual enemies
		Player* thePlayer; // Pointer to player.
		Disk* theDisk;   // The all-important floppy disk.
		
		Level(u16** LevelData, Player* _thePlayer, Vector3D startLocation, std::vector<Vector3D*> eyebotLocations, std::vector< std::vector<Vector3D> > eyebotPaths, Vector3D diskLocation); // Constructor
		void UpdateAlertStatus();
		void UpdateEnemies();
		void Draw();
		bool CheckWin();
		
	
};
