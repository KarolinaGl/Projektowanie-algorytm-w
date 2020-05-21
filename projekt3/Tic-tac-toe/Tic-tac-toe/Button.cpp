#include "Button.h"

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	float buttonX = button.getPosition().x;
	float buttonY = button.getPosition().y;
	return mouseX > buttonX && mouseX < buttonX + width && mouseY > buttonY && mouseY < button.getPosition().y + height;
}
