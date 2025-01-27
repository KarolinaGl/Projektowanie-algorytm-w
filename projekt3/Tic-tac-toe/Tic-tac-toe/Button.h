#pragma once
#include <SFML/Graphics.hpp> 

class Button
{
public:
	float width;
	float height;
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;

	Button(float XSize, float YSize, std::string buttonText);

	void setCharacterSize(int size)
	{
		text.setCharacterSize(size);
	}

	void setButtonPosition(float xOffset, float yOffset)
	{
		button.setPosition(xOffset, yOffset);
	}

	void setTextPosition(float xOffset, float yOffset)
	{
		text.setPosition(xOffset + 5, yOffset - 20);
	}

	bool isMouseOver(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window) 
	{
		window.draw(button);
		window.draw(text);
	}
};