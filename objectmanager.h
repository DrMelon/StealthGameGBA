#pragma once
// Objectmanager.h contains the definition of an Object Manager class:
// Basically, this will track all the gameobjects being used and make sure that none are created out of memory etc.

#include "gameobjects.h"
#include <vector>



class ObjectManager
{
public:
    static ObjectManager& Instance()
    {
        static ObjectManager singleton;
        return singleton;
    }

    // Vector of GameObject Pointers
    std::vector<GameObject*> objectlist;
	
	void AddObject();
	void //// TODO


private:
    //Singletons have a private constructor to prevent more than one instance.
    ObjectManager() {};
    ObjectManager(const StateStack&);             // Prevent Copying;
    ObjectManager& operator=(const StateStack&); // Prevent Assignment
};

// Initializing Singleton
static ObjectManager* g_ObjectManager = &ObjectManager::Instance();

