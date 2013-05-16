#include "levels.h"

Level::Level(u16** LevelData, Player* _thePlayer, Vector3D startLocation, std::vector<Vector3D*> eyebotLocations, std::vector< std::vector<Vector3D> > eyebotPaths, Vector3D diskLocation)
{
	// Make visible on screen
	// Fix indexing from TilED software:
	
	CopyLevelToScreenblock(28, (u16**)LevelData);
	
	thePlayer = _thePlayer;
	thePlayer->Position = startLocation;
	// Create a disk!
	theDisk = new Disk(diskLocation.X, diskLocation.Y, 8, 8, 64);

	
	for(int i = 0; i < eyebotLocations.size(); i++)
	{
		// Create an eyebot and have it follow the path of points that was passed in!
		EyeBot* thisEyebot = new EyeBot(eyebotLocations[i]->X, eyebotLocations[i]->Y, 6, 6, (i+2)*2, thePlayer);
		for(int j = 0; j < eyebotPaths[i].size(); j++)
		{
			Vector3D newPoint; // Add navigation point
			newPoint.X = eyebotPaths[i][j].X;
			newPoint.Y = eyebotPaths[i][j].Y;
			thisEyebot->pathPoints.push_back(newPoint);
		}

		// Add to list!
		eyebotInstances.push_back(thisEyebot);
	}
}

void Level::UpdateAlertStatus()
{
	for(int i = 0; i < eyebotInstances.size(); i++)
	{
		if(eyebotInstances[i]->AlertState != 0)
		{
			alertStatus = eyebotInstances[i]->AlertState;
			break;
		}
		else
		{
			alertStatus = 0;
		}
	}
}

void Level::UpdateEnemies()
{
	for(int i = 0; i < eyebotInstances.size(); i++)
	{
		eyebotInstances[i]->ScrollX = thePlayer->ScrollX;
		eyebotInstances[i]->ScrollY = thePlayer->ScrollY;
		eyebotInstances[i]->Update();

	}
	theDisk->ScrollX = thePlayer->ScrollX;
	theDisk->ScrollY = thePlayer->ScrollY;
	theDisk->Update();	
}

void Level::Draw()
{
	for(int i = 0; i < eyebotInstances.size(); i++)
	{
		eyebotInstances[i]->Draw();
	}	
	
	//draw disk
	theDisk->Draw();
}

bool Level::CheckWin()
{
	// If the player is colliding with the disk, win the level.
	if(thePlayer->Position.X > theDisk->Position.X && thePlayer->Position.Y > theDisk->Position.Y && thePlayer->Position.X < theDisk->Position.X + theDisk->Width && thePlayer->Position.Y < theDisk->Position.Y + theDisk->Height)
	{
		return true;
	}
	return false;
}




