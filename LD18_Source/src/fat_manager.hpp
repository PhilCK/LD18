// fat_manager.hpp

#ifndef __fat_manager_hpp__
#define __fat_manager_hpp__

#include "game_object.hpp"

class FatManager : public GameObject
{
public:
	FatManager() : GameObject()
	{
		objectTag = "fat_manager";
		health = 100;
	}
};

#endif