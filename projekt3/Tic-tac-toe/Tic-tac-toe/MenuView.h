#pragma once
#include <SFML/Graphics.hpp> 
#include "View.h"
#include "Window.h"

#define TEXT_SIZE 40
#define LINE_1_HEIGHT 50
#define LINE_2_HEIGHT 150
#define LINE_3_HEIGHT 250
#define LINE_4_HEIGHT 350
#define LINE_5_HEIGHT 450
#define SQUARE_BUTTON_SIZE 50
#define SUBMIT_BUTTON_WIDTH 200
#define SUBMIT_BUTTON_HEIGHT 100

class MenuView : public View
{
public:
	sf::Text chooseBoardSize;
	sf::Text chooseWinningLineLength;
	sf::Text boardSizeText;
	sf::Text winningLineLengthText;
	sf::Font font;
	Button boardSizePlusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "+");
	Button boardSizeMinusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "-");
	Button winningLineLengthMinusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "-");
	Button winningLineLengthPlusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "+");
	Button submitButton = Button(SUBMIT_BUTTON_WIDTH, SUBMIT_BUTTON_HEIGHT, "Submit");
	int boardSizeNumber = 3;
	int winningLineLengthNumber = 3;

	MenuView()
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
		initSubmitButton();
	}

	void handleEvent(sf::RenderWindow* window);

	void draw(sf::RenderWindow* window) 
	{
		window->draw(chooseBoardSize);
		boardSizeMinusButton.draw(*window);
		window->draw(boardSizeText);
		boardSizePlusButton.draw(*window);
		window->draw(chooseWinningLineLength);
		winningLineLengthMinusButton.draw(*window);
		window->draw(winningLineLengthText);
		winningLineLengthPlusButton.draw(*window);
		submitButton.draw(*window);
	}

	void initChooseBoardSize();

	void initBoardSizeMinusButton();

	void initBoardSizeText();

	void initBoardSizePlusButton();

	void initChooseWinningLineLength();

	void initWinningLineLengthMinusButton();

	void initWinningLineLengthText();

	void initWinningLineLengthPlusButton();

	void initSubmitButton();

	void boardSizeMinusButtonClicked();

	void boardSizePlusButtonClicked();

	void winningLineLengthMinusButtonClicked();

	void winningLineLengthPlusButtonClicked();

	void submitButtonClicked();
};
