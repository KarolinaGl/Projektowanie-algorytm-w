#pragma once
#include <SFML/Graphics.hpp> 

class Button
{
public:
	int xSize;
	int ySize;
	float xOffset;
	float yOffset;
	sf::RectangleShape rectangle;

	Button(int XSize, int YSize, float XOffset, float YOffset)
	{
		xSize = XSize;
		ySize = YSize;
		xOffset = XOffset;
		yOffset = YOffset;
		rectangle = sf::RectangleShape(sf::Vector2f(xSize, ySize));
		rectangle.setPosition(xOffset, yOffset);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(rectangle);
	}
};