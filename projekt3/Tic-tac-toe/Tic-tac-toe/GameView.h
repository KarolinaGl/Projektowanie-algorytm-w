#pragma once
#include "View.h"
#include "Board.h"
#include "Game.h"
#include "ScoreView.h"

#define BOARD_SIZE_IN_PIXELS 500
#define BOARD_X_OFFSET 50
#define BOARD_Y_OFFSET 50
#define MARK_OFFSET 15

class GameView : public View
{
public:
	Game game;
	Board currentBoard;
	sf::RectangleShape boardRectangle = sf::RectangleShape(sf::Vector2f(BOARD_SIZE_IN_PIXELS, BOARD_SIZE_IN_PIXELS));
	std::vector<sf::RectangleShape> gridlines;
	std::vector<sf::RectangleShape> verticalGridlines;
	std::vector<sf::RectangleShape> horizontalGridlines;
	int boardSizeNumber = 3;
	int winningLineLengthNumber = 3;

	GameView(int boardSizeNumber, int winningLineLengthNumber, bool isBotGame)
	{
		this->boardSizeNumber = boardSizeNumber;
		this->winningLineLengthNumber = winningLineLengthNumber;
		initBoard();
		initBoardRectangle();
		initGridlines("vertical", verticalGridlines);
		initGridlines("horizontal", horizontalGridlines);
		this->game = Game(&currentBoard, isBotGame);
	}

	void handleEvent(sf::RenderWindow* renderWindow, Window* window);

	void draw(sf::RenderWindow* window);

	void drawMark(sf::RenderWindow& window, int i, int j, char mark);

	void initBoard();

	void initBoardRectangle();

	void initGridlines(std::string direction, std::vector<sf::RectangleShape>& directionalGridlines);

	bool isGameFinished(Window* window);
};


