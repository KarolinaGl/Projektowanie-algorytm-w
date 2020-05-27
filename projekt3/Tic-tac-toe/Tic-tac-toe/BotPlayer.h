#pragma once
#include "Board.h"
#include <random>
#include <cstdlib>

class BotPlayer
{
public:

	Board* currentBoard;
	char botMark = 'X';
	char playerMark = 'O';

	BotPlayer() {}

	BotPlayer(Board* currentBoard)
	{
		this->currentBoard = currentBoard;
	}
};