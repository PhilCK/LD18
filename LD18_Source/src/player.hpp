// player.hpp

#ifndef __player_hpp__
#define __player_hpp__

#include "game_object.hpp"
#include "manager.hpp"
#include <algorithm>

using std::min;
using std::max;

class Player : public GameObject
{

	enum Movement {
		MOVE_CENTER,
		MOVE_LEFT,
		MOVE_RIGHT,
		THROW_CENTER,
		THROW_LEFT,
		THROW_RIGHT
	};

	Movement currentMovement;

public:

	enum PlayerState
	{
		NORMAL_STATE,
		HOLDING_A_MANAGER_STATE,
		THROWING_A_MANAGER_STATE
	};

	PlayerState currentState;


	Player() : GameObject()
	{
		xSize = 30;
		ySize = 30;
		y = 100 - ySize; // 100 is where building starts
		x = (Screen::Width / 2) - (xSize / 2);
		objectTag = "player";
		health = 1;

		currentMovement = MOVE_CENTER;
		currentState = NORMAL_STATE;
	}

	bool update()
	{
		int xDiff = windowInstance().input().mouseX() - (Screen::Width / 2);

		if (xDiff > 0)
			currentMovement = MOVE_RIGHT;
		else if(xDiff < 0)
			currentMovement = MOVE_LEFT;

		x += xDiff;

		x = min(x, Screen::Width - 47 - (xSize));
		x = max(x, 47);

		windowInstance().input().setMousePosition(Screen::Width / 2, 100);

		return true;
	}

	void draw()
	{
		static Gosu::Image move_center(windowInstance().graphics(), Directory::MediaDir + L"hero_move_center.png", false);
		static Gosu::Image move_left(windowInstance().graphics(), Directory::MediaDir + L"hero_move_left.png", false);
		static Gosu::Image move_right(windowInstance().graphics(), Directory::MediaDir + L"hero_move_right.png", false);
		static Gosu::Image throw_center(windowInstance().graphics(), Directory::MediaDir + L"hero_throw_center.png", false);
		static Gosu::Image throw_left(windowInstance().graphics(), Directory::MediaDir + L"hero_throw_left.png", false);
		static Gosu::Image throw_right(windowInstance().graphics(), Directory::MediaDir + L"hero_throw_right.png", false);

		switch(currentMovement)
		{
		case MOVE_CENTER:
			move_center.draw(x, y, Layer::PLAYER_LAYER);
			break;
		case MOVE_LEFT:
			move_left.draw(x, y, Layer::PLAYER_LAYER);
			break;
		case MOVE_RIGHT:
			move_right.draw(x, y, Layer::PLAYER_LAYER);
			break;
		case THROW_CENTER:
			throw_center.draw(x, y, Layer::PLAYER_LAYER);
			break;
		case THROW_LEFT:
			throw_left.draw(x, y, Layer::PLAYER_LAYER);
			break;
		case THROW_RIGHT:
			throw_right.draw(x, y, Layer::PLAYER_LAYER);
			
		};
	}

};


#endif