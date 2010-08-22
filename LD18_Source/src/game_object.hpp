// game_object.hpp

#ifndef __game_object_hpp__
#define __game_object_hpp__

#include <Gosu/Gosu.hpp>
#include <boost/utility.hpp>
#include <string>

#include "window.hpp"
#include "base.hpp"

using std::string;
using namespace Base;


class GameObject
{
public:

	bool magicBool;

	GameObject()
	{
		fallmeter = 0;
		collidable = true;
	}

	int x, y;
	int xSize, ySize;
	int health;
	bool collidable;
	string objectTag;

	int fallmeter;
	static const int maxfall = 100;

	virtual bool update() { return true; };
	virtual void draw() = 0;

};

#endif