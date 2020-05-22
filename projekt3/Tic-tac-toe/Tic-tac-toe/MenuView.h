#pragma once
#include "View.h"

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
	sf::Font font;
	sf::Text chooseBoardSize;
	sf::Text chooseWinningLineLength;
	sf::Text boardSizeText;
	sf::Text winningLineLengthText;
	Button boardSizePlusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "+");
	Button boardSizeMinusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "-");
	Button winningLineLengthMinusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "-");
	Button winningLineLengthPlusButton = Button(SQUARE_BUTTON_SIZE, SQUARE_BUTTON_SIZE, "+");
	Button submitButton = Button(SUBMIT_BUTTON_WIDTH, SUBMIT_BUTTON_HEIGHT, "Submit");
	int boardSizeNumber = 3;
	int winningLineLengthNumber = 3;

	MenuView();

	void handleEvent(sf::RenderWindow* renderWindow, Window* window);

	void draw(sf::RenderWindow* window);

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

	void submitButtonClicked(Window* window);
};
