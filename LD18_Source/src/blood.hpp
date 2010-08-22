// blood.hpp

#ifndef __blood_hpp__
#define __blood_hpp__

#include "game_object.hpp"

class Blood : public GameObject
{

	int type;
	unsigned long lifetime;
	Gosu::Color bloodAlpha;
	int alpha;

public:
	Blood(int setx, int sety) : GameObject()
	{
		collidable = false;
		objectTag = "blood";
		x = setx;
		y = sety;

		type = (rand() % 2) + 1;

		lifetime = Gosu::milliseconds() + 10000;
		alpha = 255;
		bloodAlpha.setAlpha(alpha);
		bloodAlpha.setBlue(255);
		bloodAlpha.setRed(255);
		bloodAlpha.setGreen(255);
	}

	bool update()
	{
		bloodAlpha.setAlpha(alpha -= 1);
		//return (lifetime > Gosu::milliseconds() ? true : false);
		return (alpha ? true : false);
	}

	void draw()
	{
		if (type == 1) {
			static Gosu::Image blood1(windowInstance().graphics(), Directory::MediaDir + L"blood1.png", false);
			blood1.draw(x, y, Layer::BLOOD_SPLATTER_LAYER, 1, 1, bloodAlpha);
		}

		if (type == 2) {
			static Gosu::Image blood2(windowInstance().graphics(), Directory::MediaDir + L"blood2.png", false);
			blood2.draw(x, y, Layer::BLOOD_SPLATTER_LAYER, 1, 1, bloodAlpha);
		}

	}


};


#endif