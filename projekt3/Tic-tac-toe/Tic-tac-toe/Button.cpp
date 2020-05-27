#include "Button.h"

Button::Button(float XSize, float YSize, std::string buttonText)
{
	width = XSize;
	height = YSize;
	button = sf::RectangleShape(sf::Vector2f(width, height));
	button.setFillColor(sf::Color::White);
	font.loadFromFile("arial.ttf");
	text.setString(buttonText);
	text.setStyle(sf::Text::Bold);
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = (float) sf::Mouse::getPosition(window).x;
	float mouseY = (float) sf::Mouse::getPosition(window).y;
	float buttonX = button.getPosition().x;
	float buttonY = button.getPosition().y;
	return mouseX > buttonX && mouseX < buttonX + width && mouseY > buttonY && mouseY < button.getPosition().y + height;
}
