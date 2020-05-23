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

	std::pair<int, int> makeMove()
	{/*
		std::vector<std::pair<int, int>> moves;
		for (int i = 0; i < currentBoard->boardSize; ++i)
		{
			for (int j = 0; j < currentBoard->boardSize; ++j)
			{
				if (currentBoard->board[i][j] == ' ')
					moves.push_back({ i, j });
			}
		}
		srand(time(NULL));
		int randomNumber = rand() % moves.size();
		return moves[randomNumber];*/
	}
};