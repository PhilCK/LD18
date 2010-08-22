// zombie.hpp

#ifndef __zombie_hpp__
#define __zombie_hpp__

#include "game_object.hpp"
#include "blood.hpp"


class Zombie : public GameObject
{

	enum ZombieState {
		ZOMBIE_SPAWN,
		ZOMBIE_CLIMB,
		ZOMBIE_ROOF
	};

	enum WalkState {
		LEFT,
		RIGHT
	};

	ZombieState currentState;
	WalkState walkDir;
	
	int climbAt;

public:

	Zombie() : GameObject()
	{
		objectTag = "zombie";
		ySize = 30;
		xSize = 30;

		y = Screen::Height - ySize;
		x = -10 + ((rand() % 2) * 620);
		climbAt = (rand() % (475 - xSize)) + (50);
		health = 1;

		collidable = false;

		currentState = ZOMBIE_SPAWN;	
	}

	bool update()
	{
		if (health > 0)
		{
			switch(currentState)
			{
			case ZOMBIE_CLIMB:
				if (y not_eq (100 - ySize))
					y--;
				else
				{
					currentState = ZOMBIE_ROOF;
				}
				break;
			case ZOMBIE_SPAWN:
				
				if(x > climbAt)
				{
					walkDir = LEFT;
					x -= 1;
				}
				else
				{
					walkDir = RIGHT;
					x += 1;
				}

				if (x == climbAt)
				{
					currentState = ZOMBIE_CLIMB;
					collidable = true;
				}

				break;

			case ZOMBIE_ROOF:

				if(x > objectManagerInstance().getObject("player").x)
				{
					walkDir = LEFT;
					x -= 1;
				}
				else
				{
					walkDir = RIGHT;
					x += 1;
				}
			}

	
		}
		else
		{
			if (not fallmeter)
			{
				objectManagerInstance().push(new Blood(x, y));
				static Gosu::Sample hurt(windowInstance().audio(), Directory::MediaDir + L"hit.wav");

				hurt.play(0.1);
			}

			y += 4;
			fallmeter += 4;
		}

		return(fallmeter < maxfall ? true : false);
	}

	void draw()
	{
		static Gosu::Image zombieClimb1(windowInstance().graphics(), Directory::MediaDir + L"zombie_climb_1.png", false);
		static Gosu::Image zombieClimb2(windowInstance().graphics(), Directory::MediaDir + L"zombie_climb_2.png", false);
		static Gosu::Image zombieWalkLeft(windowInstance().graphics(), Directory::MediaDir + L"zombie_walk_left.png", false);
		static Gosu::Image zombieWalkRight(windowInstance().graphics(), Directory::MediaDir + L"zombie_walk_right.png", false);

		if (currentState == ZOMBIE_CLIMB)
		{

			if (Gosu::milliseconds() / 100 % 2)
				zombieClimb1.draw(x, y, Layer::ZOMBIE_LAYER);
			else
				zombieClimb2.draw(x, y, Layer::ZOMBIE_LAYER);
		}
		else
		{
			if (walkDir == LEFT)
				zombieWalkLeft.draw(x, y, Layer::ZOMBIE_LAYER);
			else
				zombieWalkRight.draw(x, y, Layer::ZOMBIE_LAYER);
		}	

	}
};


#endif