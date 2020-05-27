#include "MenuView.h"
#include "GameView.h"
#include "Window.h"

MenuView::MenuView()
{
	font.loadFromFile("arial.ttf");
	initChooseBoardSize();
	initBoardSizeMinusButton();
	initBoardSizeText();
	initBoardSizePlusButton();
	initChooseWinningLineLength();
	initWinningLineLengthMinusButton();
	initWinningLineLengthText();
	initWinningLineLengthPlusButton();
	initBotGameButton();
	initPlayerGameButton();
}

void MenuView::handleEvent(sf::RenderWindow* renderWindow, Window* window)
{
	if (boardSizeMinusButton.isMouseOver(*renderWindow))
		boardSizeMinusButtonClicked();
	if (boardSizePlusButton.isMouseOver(*renderWindow))
		boardSizePlusButtonClicked();
	if (winningLineLengthMinusButton.isMouseOver(*renderWindow))
		winningLineLengthMinusButtonClicked();
	if (winningLineLengthPlusButton.isMouseOver(*renderWindow))
		winningLineLengthPlusButtonClicked();
	if (botGameButton.isMouseOver(*renderWindow))
		botGameButtonClicked(window);
	if (playerGameButton.isMouseOver(*renderWindow))
		playerGameButtonClicked(window);
}

void MenuView::draw(sf::RenderWindow* window)
{
	window->draw(chooseBoardSize);
	boardSizeMinusButton.draw(*window);
	window->draw(boardSizeText);
	boardSizePlusButton.draw(*window);
	window->draw(chooseWinningLineLength);
	winningLineLengthMinusButton.draw(*window);
	window->draw(winningLineLengthText);
	winningLineLengthPlusButton.draw(*window);
	botGameButton.draw(*window);
	playerGameButton.draw(*window);
}

void MenuView::initChooseBoardSize()
{
	chooseBoardSize.setFont(font);
	chooseBoardSize.setString("Board size:");
	chooseBoardSize.setCharacterSize(TEXT_SIZE);
	chooseBoardSize.setFillColor(sf::Color::White);
	chooseBoardSize.setStyle(sf::Text::Bold);
	chooseBoardSize.setPosition(WINDOW_X_SIZE / 2 - chooseBoardSize.getLocalBounds().width / 2, LINE_1_HEIGHT);
}

void MenuView::initBoardSizeMinusButton()
{
	boardSizeMinusButton.setButtonPosition(WINDOW_X_SIZE / 3, LINE_2_HEIGHT);
	boardSizeMinusButton.setTextPosition(WINDOW_X_SIZE / 3 + 8, LINE_2_HEIGHT - 8);
	boardSizeMinusButton.setCharacterSize(70);
}

void MenuView::initBoardSizeText()
{
	boardSizeText.setFont(font);
	boardSizeText.setString(std::to_string(boardSizeNumber));
	boardSizeText.setCharacterSize(TEXT_SIZE);
	boardSizeText.setFillColor(sf::Color::White);
	boardSizeText.setStyle(sf::Text::Bold);
	boardSizeText.setPosition(WINDOW_X_SIZE / 2 - boardSizeText.getLocalBounds().width / 2, LINE_2_HEIGHT);
}

void MenuView::initBoardSizePlusButton()
{
	boardSizePlusButton.setButtonPosition(WINDOW_X_SIZE * 2 / 3 - SQUARE_BUTTON_SIZE, LINE_2_HEIGHT);
	boardSizePlusButton.setTextPosition(WINDOW_X_SIZE * 2 / 3 - SQUARE_BUTTON_SIZE, LINE_2_HEIGHT);
	boardSizePlusButton.setCharacterSize(70);
}

void MenuView::initChooseWinningLineLength()
{
	chooseWinningLineLength.setFont(font);
	chooseWinningLineLength.setString("Winning line length:");
	chooseWinningLineLength.setCharacterSize(TEXT_SIZE);
	chooseWinningLineLength.setFillColor(sf::Color::White);
	chooseWinningLineLength.setStyle(sf::Text::Bold);
	chooseWinningLineLength.setPosition(WINDOW_X_SIZE / 2 - chooseWinningLineLength.getLocalBounds().width / 2, LINE_3_HEIGHT);
}

void MenuView::initWinningLineLengthMinusButton()
{
	winningLineLengthMinusButton.setButtonPosition(WINDOW_X_SIZE / 3, LINE_4_HEIGHT);
	winningLineLengthMinusButton.setTextPosition(WINDOW_X_SIZE / 3 + 8, LINE_4_HEIGHT - 8);
	winningLineLengthMinusButton.setCharacterSize(70);
}

void MenuView::initWinningLineLengthText()
{
	winningLineLengthText.setFont(font);
	winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
	winningLineLengthText.setCharacterSize(TEXT_SIZE);
	winningLineLengthText.setFillColor(sf::Color::White);
	winningLineLengthText.setStyle(sf::Text::Bold);
	winningLineLengthText.setPosition(WINDOW_X_SIZE / 2 - boardSizeText.getLocalBounds().width / 2, LINE_4_HEIGHT);
}

void MenuView::initWinningLineLengthPlusButton()
{
	winningLineLengthPlusButton.setButtonPosition(WINDOW_X_SIZE * 2 / 3 - SQUARE_BUTTON_SIZE, LINE_4_HEIGHT);
	winningLineLengthPlusButton.setTextPosition(WINDOW_X_SIZE * 2 / 3 - SQUARE_BUTTON_SIZE, LINE_4_HEIGHT);
	winningLineLengthPlusButton.setCharacterSize(70);
}

void MenuView::initBotGameButton()
{
	botGameButton.setButtonPosition(WINDOW_X_SIZE / 4 - SUBMIT_BUTTON_WIDTH / 2, LINE_5_HEIGHT);
	botGameButton.setTextPosition(WINDOW_X_SIZE / 4 - SUBMIT_BUTTON_WIDTH / 2 + 70, LINE_5_HEIGHT + 40);
	botGameButton.setCharacterSize(TEXT_SIZE);
}

void MenuView::initPlayerGameButton()
{
	playerGameButton.setButtonPosition(WINDOW_X_SIZE * 3/ 4 - SUBMIT_BUTTON_WIDTH / 2, LINE_5_HEIGHT);
	playerGameButton.setTextPosition(WINDOW_X_SIZE * 3 / 4 - SUBMIT_BUTTON_WIDTH / 2 + 30, LINE_5_HEIGHT + 40);
	playerGameButton.setCharacterSize(TEXT_SIZE);
}

void MenuView::boardSizeMinusButtonClicked()
{
	if (boardSizeNumber >= 4)
	{
		boardSizeNumber--;
		boardSizeText.setString(std::to_string(boardSizeNumber));
		boardSizeText.setPosition(WINDOW_X_SIZE / 2 - boardSizeText.getLocalBounds().width / 2, LINE_2_HEIGHT);
		winningLineLengthNumber = std::min(winningLineLengthNumber, boardSizeNumber);
		winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
		winningLineLengthText.setPosition(WINDOW_X_SIZE / 2 - winningLineLengthText.getLocalBounds().width / 2, LINE_4_HEIGHT);
	}
}

void MenuView::boardSizePlusButtonClicked()
{
	boardSizeNumber++;
	boardSizeText.setString(std::to_string(boardSizeNumber));
	boardSizeText.setPosition(WINDOW_X_SIZE / 2 - boardSizeText.getLocalBounds().width / 2, LINE_2_HEIGHT);
}

void MenuView::winningLineLengthMinusButtonClicked()
{
	if (winningLineLengthNumber >= 4)
	{
		winningLineLengthNumber--;
		winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
		winningLineLengthText.setPosition(WINDOW_X_SIZE / 2 - winningLineLengthText.getLocalBounds().width / 2, LINE_4_HEIGHT);
	}
}

void MenuView::winningLineLengthPlusButtonClicked()
{
	if (winningLineLengthNumber < boardSizeNumber)
	{
		winningLineLengthNumber++;
		winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
		winningLineLengthText.setPosition(WINDOW_X_SIZE / 2 - winningLineLengthText.getLocalBounds().width / 2, LINE_4_HEIGHT);
	}
}

void MenuView::botGameButtonClicked(Window* window)
{
	GameView* gameView = new GameView(boardSizeNumber, winningLineLengthNumber, true);
	window->changeView(gameView);
}

void MenuView::playerGameButtonClicked(Window* window)
{
	GameView* gameView = new GameView(boardSizeNumber, winningLineLengthNumber, false);
	window->changeView(gameView);
}
