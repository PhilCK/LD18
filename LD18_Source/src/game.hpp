// game.hpp

#ifndef __game_hpp__
#define __game_hpp__

#include <algorithm>
#include "base.hpp"
#include "window.hpp"
#include "player.hpp"
#include "manager.hpp"
#include "zombie.hpp"
#include "object_manager.hpp"

using namespace Base;

class Game
{

	enum GameState {
		TITLESCREEN,
		GAMEMODE,
		GAMEOVER
	};

	GameState currentState;

	unsigned long gameTimer;
	unsigned long lastFrame;

	unsigned long score;

public:

	bool firstHint;

	Game()
	{
		currentState = TITLESCREEN;
		objectManagerInstance().push(new Player);
		objectManagerInstance().push(new Manager);
		score = 0;
		gameTimer = 0;
		lastFrame = Gosu::milliseconds();

		firstHint = true;
	}

	void update()
	{
		if (currentState == GAMEMODE)
		{
			objectManagerInstance().update();
			
			gameTimer += Gosu::milliseconds() - lastFrame;
			lastFrame  = Gosu::milliseconds();

			if (gameTimer > 5000)
			{
				objectManagerInstance().push(new Zombie);
				score += 1;
				gameTimer = 0 + min((int)(score * 100), 4500);
			}

			if (objectManagerInstance().getObject("player").health < 0)
			{
				objectManagerInstance().clear();
				currentState = GAMEOVER;
			}
		}
	}

	void draw()
	{
		if (currentState == TITLESCREEN)
		{
			static Gosu::Image intro(windowInstance().graphics(),
			 Directory::MediaDir + L"intro.png", false);

			intro.draw(0, 0, Layer::UI_LAYER);
		}
		else if (currentState == GAMEMODE)
		{
			drawBuilding();
			drawBackground();
			objectManagerInstance().draw();

			if (firstHint)
			{
				static Gosu::Image hint1(windowInstance().graphics(), Directory::MediaDir + L"hint1.png", false); 
				hint1.draw(150, 320, Layer::UI_LAYER);
	
				static Gosu::Image hint2(windowInstance().graphics(), Directory::MediaDir + L"hint2.png", false); 
				hint2.draw(150, 360, Layer::UI_LAYER);
			}

		}
		else if (currentState == GAMEOVER)
		{
			static Gosu::Image gameover(windowInstance().graphics(),
			 Directory::MediaDir + L"game_over.png", false);

			gameover.draw(0, 0, Layer::UI_LAYER);
		}

	}

	void buttonUp(Gosu::Button button)
	{

		if (currentState == GAMEMODE)
		{
			if (button == Gosu::msLeft)
			{
				if(firstHint)
					firstHint = false;
			}
		}

		if (currentState == TITLESCREEN)
			currentState = GAMEMODE;

		if (currentState == GAMEOVER)
		{
			currentState = GAMEMODE;
			objectManagerInstance().push(new Player);
			objectManagerInstance().push(new Manager);
			score = 0;
		}

	}

private:
	
	void drawBuilding()
	{
		 static Gosu::Image buildingBody(windowInstance().graphics(),
			 Directory::MediaDir + L"building.png", false);

		 buildingBody.draw(47, 100, Layer::BUILDING_LAYER);
	}

	void drawBackground()
	{
		static Gosu::Image background(windowInstance().graphics(), Directory::MediaDir + L"bg.png", false); 
		background.draw(0, 0, Layer::BACKGROUND_LAYER);
	}
};

#endif