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

	Button(float XSize, float YSize, std::string buttonText)
	{
		width = XSize;
		height = YSize;
		button = sf::RectangleShape(sf::Vector2f(width, height));
		text.setString(buttonText);
		text.setStyle(sf::Text::Bold);
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		button.setFillColor(sf::Color::White);
	}

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

	void setTextColor(sf::Color color) 
	{
		text.setFillColor(color);
	}

	bool isMouseOver(sf::RenderWindow& window) 
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		float buttonX = button.getPosition().x;
		float buttonY = button.getPosition().y;
		return mouseX > buttonX && mouseX < buttonX + width && mouseY > buttonY && mouseY < button.getPosition().y + height;
	}

	void draw(sf::RenderWindow& window) 
	{
		window.draw(button);
		window.draw(text);
	}
};