#include "ScoreView.h"
#include "Window.h"

void ScoreView::handleEvent(sf::RenderWindow* renderWindow, Window* window)
{
	if (playAgainButton.isMouseOver(*renderWindow))
		playAgainButtonClicked(window);
}

void ScoreView::draw(sf::RenderWindow* window)
{
	window->draw(scoreText);
	playAgainButton.draw(*window);
}

void ScoreView::initScoreText()
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

void ScoreView::initPlayAgainButton()
{
	playAgainButton.setButtonPosition(WINDOW_X_SIZE / 2 - BUTTON_WIDTH / 2, WINDOW_Y_SIZE / 2);
	playAgainButton.setTextPosition(WINDOW_X_SIZE / 2 - BUTTON_WIDTH / 2 + 30, WINDOW_Y_SIZE / 2 + 40);
	playAgainButton.setCharacterSize(50);
}

void ScoreView::playAgainButtonClicked(Window* window)
{
	MenuView* menuView = new MenuView();
	window->changeView(menuView);
}
