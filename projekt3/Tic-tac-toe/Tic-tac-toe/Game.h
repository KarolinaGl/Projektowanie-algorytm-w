#pragma once
#include "Board.h"

class Game
{
public:
	Board* currentBoard;
	int currentNumberOfMarks = 0;
	int maxNumberOfMarks;

    Game() {}

	Game(Board* currentBoard)
	{
        this->currentBoard = currentBoard;
		maxNumberOfMarks = currentBoard->boardSize * currentBoard->boardSize;
	}

    bool isWon(char mark)
    {
        currentNumberOfMarks++;
        int sameMarksCounter = 0;
        int smallerRange = currentBoard->boardSize - currentBoard->winningLineLength + 1;
        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j] == mark)
                        sameMarksCounter++;
                }
                if (sameMarksCounter == currentBoard->winningLineLength)
                    return true;
                sameMarksCounter = 0;
            }
        }

        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < smallerRange; ++j)
            {
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i][j + k] == mark)
                        sameMarksCounter++;
                }
                if (sameMarksCounter == currentBoard->winningLineLength)
                    return true;
                sameMarksCounter = 0;
            }
        }

        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = 0; j < smallerRange; ++j)
            {
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j + k] == mark)
                        sameMarksCounter++;
                }
                if (sameMarksCounter == currentBoard->winningLineLength)
                    return true;
                sameMarksCounter = 0;
            }
        }

        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = currentBoard->winningLineLength - 1; j < currentBoard->boardSize; ++j)
            {
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j - k] == mark)
                        sameMarksCounter++;
                }
                if (sameMarksCounter == currentBoard->winningLineLength)
                    return true;
                sameMarksCounter = 0;
            }
        }
        return false;
    }

    bool isDraw()
    {
        return currentNumberOfMarks == maxNumberOfMarks;
    }
};
