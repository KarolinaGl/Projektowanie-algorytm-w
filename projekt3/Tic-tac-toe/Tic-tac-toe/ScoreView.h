#pragma once
#include "View.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100

class ScoreView : public View
{
public:
	std::string winner;
	sf::Font font;
	sf::Text scoreText;
	Button playAgainButton = Button(BUTTON_WIDTH, BUTTON_HEIGHT, "Play again");

	ScoreView(std::string winner);

	void handleEvent(sf::RenderWindow* renderWindow, Window* window);

	void draw(sf::RenderWindow* window);

	void initScoreText();

	void initPlayAgainButton();

	void playAgainButtonClicked(Window* window);
};
