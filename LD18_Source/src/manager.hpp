// manager.hpp

#ifndef __manager_hpp__
#define __manager_hpp__


#include <boost/lexical_cast.hpp>
#include "game_object.hpp"


class Manager : public GameObject
{

	int speach;
	unsigned long speachTimer;

public:

	enum ManagerStates
	{
		VOID_STATE,
		SPAWN_STATE,
		HOVER_STATE,
		THROWN_STATE
	};

	ManagerStates currentState;


	Manager() : GameObject()
	{		
		xSize = 30;
		ySize = 30;

		y = 100 - ySize;

		while (true) {
			x = (rand() % 450) + 52;
			if (Gosu::distance(x, y,  objectManagerInstance().getObject("player").x,  objectManagerInstance().getObject("player").y) > 70)
				break;
		}
		

		objectTag = "manager";
		health = 10;
		collidable = false;

		speach = rand() % 10;
		speachTimer = Gosu::milliseconds() - 1;

		currentState = VOID_STATE;

		magicBool = false;
	}


	bool update()
	{
		if (currentState == THROWN_STATE)
		{
			magicBool = true;

			if (y > 100)
				collidable = true;

			if (health <= 0)
			{
				fallmeter += 4;
			}

			y += 4;

			if (y > Screen::Height)
				fallmeter = 100;
		}

		else if (currentState == HOVER_STATE)
		{
			magicBool = true;

			x = objectManagerInstance().getObject("player").x;
			if (windowInstance().input().down(Gosu::msLeft))
			{
				currentState = THROWN_STATE;
				static Gosu::Sample thrown(windowInstance().audio(), Directory::MediaDir + L"throw.wav");
				thrown.play(0.005);
				objectManagerInstance().push(new Manager);
			}
		}
		
		else if (currentState == SPAWN_STATE)
		{
			if ((objectManagerInstance().getObject("player").x + objectManagerInstance().getObject("player").xSize > x) and 
				(objectManagerInstance().getObject("player").x < x + xSize))
			{
				currentState = HOVER_STATE;
				y -= objectManagerInstance().getObject("player").ySize;
				speachTimer = Gosu::milliseconds() + 1000;

				static Gosu::Sample hover(windowInstance().audio(), Directory::MediaDir + L"pickup.wav");
				hover.play(0.005);
			}
		}

		else if (currentState == VOID_STATE)
		{
			if (not windowInstance().input().down(Gosu::msLeft))
			{
				currentState = SPAWN_STATE;
			}
		}

		return(fallmeter < maxfall ? true : false);

	}

	void draw()
	{

		static Gosu::Image hover(windowInstance().graphics(), Directory::MediaDir + L"manager_pickup.png", false);
		static Gosu::Image thrown(windowInstance().graphics(), Directory::MediaDir + L"manager_throw.png", false);
		static Gosu::Image standing(windowInstance().graphics(), Directory::MediaDir + L"manager_standing.png", false);

		switch(currentState)
		{
		case HOVER_STATE:
			hover.draw(x, y + 16, Layer::PEOPLE_THROWN_LAYER);
			break;
		case THROWN_STATE:
			thrown.draw(x, y, Layer::PEOPLE_THROWN_LAYER);
			break;
		default:
			standing.draw(x, y, Layer::PEOPLE_THROWN_LAYER);
		};
		
		
		static Gosu::Image bubble0(windowInstance().graphics(), Directory::MediaDir + L"speech0.png", false);
		static Gosu::Image bubble1(windowInstance().graphics(), Directory::MediaDir + L"speech1.png", false);
		static Gosu::Image bubble2(windowInstance().graphics(), Directory::MediaDir + L"speech2.png", false);
		static Gosu::Image bubble3(windowInstance().graphics(), Directory::MediaDir + L"speech3.png", false);
		static Gosu::Image bubble4(windowInstance().graphics(), Directory::MediaDir + L"speech4.png", false);
		static Gosu::Image bubble5(windowInstance().graphics(), Directory::MediaDir + L"speech5.png", false);
		static Gosu::Image bubble6(windowInstance().graphics(), Directory::MediaDir + L"speech6.png", false);
		static Gosu::Image bubble7(windowInstance().graphics(), Directory::MediaDir + L"speech7.png", false);
		static Gosu::Image bubble8(windowInstance().graphics(), Directory::MediaDir + L"speech8.png", false);
		static Gosu::Image bubble9(windowInstance().graphics(), Directory::MediaDir + L"speech9.png", false);


		if (speachTimer > Gosu::milliseconds())
		{
			switch(speach)
			{
			case 0:
				bubble0.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 1:
				bubble1.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 2:
				bubble2.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 3:
				bubble3.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 4:
				bubble4.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 5:
				bubble5.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 6:
				bubble6.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 7:
				bubble7.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 8:
				bubble8.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			case 9:
				bubble9.draw(x - 50, y - 55, Layer::PEOPLE_THROWN_LAYER);
				break;
			}
		}
	}

};


#endif