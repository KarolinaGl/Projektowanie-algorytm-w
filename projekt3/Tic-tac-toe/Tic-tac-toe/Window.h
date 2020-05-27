#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Button.h"
#include "View.h"
#include "MenuView.h"
#include "GameView.h"
#include "Constants.h"


class Window
{
public:
	View* view;
	sf::RenderWindow* window;

	Window();

	void run();

	void changeView(View* newView)
	{
		delete view;
		view = newView;
	}
};
