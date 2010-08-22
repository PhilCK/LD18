// window_win.cpp

#include <Gosu/Autolink.hpp>
#include <iso646.h>
#include "window.hpp"
#include "game.hpp"
#include "object_manager.hpp"

class GameWindow : public Gosu::Window
{

	Game game;

public:
	GameWindow()
		: Gosu::Window(Screen::Width, Screen::Height, Screen::Fullscreen)
	{
		setCaption(L"LD 18");
	}


	void draw()
	{
		game.draw();

	}


	void update()
	{
		game.update();
		
		if (input().down(Gosu::kbEscape))
			close();
	}

	void buttonUp(Gosu::Button button)
	{
		game.buttonUp(button);
	}


};

Gosu::Window& windowInstance() {
	static GameWindow game;
	return game;
}


int main()
{
	windowInstance().show();
}