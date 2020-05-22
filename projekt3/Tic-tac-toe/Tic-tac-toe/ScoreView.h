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

	ScoreView(std::string winner)
	{
		this->winner = winner;
		font.loadFromFile("arial.ttf");
		initScoreText();
		initPlayAgainButton();
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(scoreText);
		playAgainButton.draw(*window);
	}

	void initScoreText()
	{
		if (winner == " ")
			scoreText.setString("It's a draw!");
		else
			scoreText.setString(winner + " player won!");
		scoreText.setFont(font);
		scoreText.setCharacterSize(70);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setStyle(sf::Text::Bold);
		scoreText.setPosition(WINDOW_X_SIZE / 2 - scoreText.getLocalBounds().width / 2, 100);
	}

	void initPlayAgainButton()
	{
		playAgainButton.setButtonPosition(WINDOW_X_SIZE / 2 - BUTTON_WIDTH / 2, WINDOW_Y_SIZE / 2);
		playAgainButton.setTextPosition(WINDOW_X_SIZE / 2 - BUTTON_WIDTH / 2 + 30, WINDOW_Y_SIZE / 2 + 40);
		playAgainButton.setCharacterSize(50);
	}
};
