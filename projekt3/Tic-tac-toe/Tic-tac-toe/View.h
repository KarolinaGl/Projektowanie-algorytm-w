#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Constants.h"

class Window;

class View
{
public:

	View() {}

	virtual void handleEvent(sf::RenderWindow* renderWindow, Window* window) {}

	virtual void draw(sf::RenderWindow* window) {}

	virtual void additionalAction(Window* window) {}
};
