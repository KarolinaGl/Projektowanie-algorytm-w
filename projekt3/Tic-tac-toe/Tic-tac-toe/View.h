#pragma once

class View
{
public:

	View()
	{

	}

	virtual void handleEvent(sf::RenderWindow* window) {}

	virtual void draw(sf::RenderWindow* window) {}
};
