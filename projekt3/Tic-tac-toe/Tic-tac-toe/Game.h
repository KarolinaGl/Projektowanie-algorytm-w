#pragma once
#include <algorithm>
#include "Board.h"
#include "BotPlayer.h"
#include <iostream>

class Game
{
public:
	Board* currentBoard;
    BotPlayer bot;
	int currentNumberOfMarks = 0;
	int maxNumberOfMarks;
    bool isBotGame;
    bool isBotMove;

    Game() {}

	Game(Board* currentBoard, bool isBotGame)
	{
        isBotMove = true;
        this->currentBoard = currentBoard;
		maxNumberOfMarks = currentBoard->boardSize * currentBoard->boardSize;
        this->isBotGame = isBotGame;
        bot = BotPlayer(currentBoard);
        if (isBotGame)
            makeBotMove();
    }

    bool isWon(char mark)
    {
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

    void makeBotMove()
    {
        if (isBotMove)
        {
            std::pair<int, int> rowAndColumn = findBestMove();
            fieldClicked(rowAndColumn.first, rowAndColumn.second);
        }
    }

    void fieldClicked(int row, int column)
    {
        if (row != -1 && column != -1 && currentBoard->board[row][column] == ' ')
        {
            currentNumberOfMarks++;
            isBotMove = !isBotMove;
            if (currentNumberOfMarks % 2 == 0)
                currentBoard->board[row][column] = 'O';
            else
                currentBoard->board[row][column] = 'X';
        }
    }

    int evaluate(Board* currentBoard)
    {
        if (isWon(bot.botMark))
            return 10;
        if (isWon(bot.playerMark))
            return -10;
        return 0;
    }

    int miniMax(Board* currentBoard, int depth, int alpha, int beta, bool isMax)
    {
        int score = evaluate(currentBoard);

        if (score == 10)
            return score;
        if (score == -10)
            return score;
        if (isDraw())
            return 0;
        if (depth == 0)
            return score;

        if (isMax)
        {
            int best = -100000;
            for (int i = 0; i < currentBoard->boardSize; ++i)
            {
                for (int j = 0; j < currentBoard->boardSize; ++j)
                {
                    if (currentBoard->board[i][j] == ' ')
                    {
                        currentBoard->board[i][j] == bot.botMark;
                        int eval = miniMax(currentBoard, depth - 1, alpha, beta, false);
                        best = std::max(best, eval);
                        alpha = std::max(alpha, eval);
                        currentBoard->board[i][j] = ' ';
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return best;
        }
        else
        {
            int best = 100000;
            for (int i = 0; i < currentBoard->boardSize; ++i)
            {
                for (int j = 0; j < currentBoard->boardSize; ++j)
                {
                    if (currentBoard->board[i][j] == ' ')
                    {
                        currentBoard->board[i][j] == bot.playerMark;
                        int eval = miniMax(currentBoard, depth - 1, alpha, beta, true);
                        best = std::min(best, eval);
                      
                        currentBoard->board[i][j] = ' ';
                        beta = std::min(beta, eval);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return best;
        }
    }

    std::pair<int, int> findBestMove()
    {
        int bestValue = -1000;
        std::pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                if (currentBoard->board[i][j] == ' ')
                {
                    currentBoard->board[i][j] = bot.botMark;

                    int moveValue = miniMax(currentBoard, 9, -100000, 100000, false);

                    currentBoard->board[i][j] = ' ';

                    if (moveValue > bestValue)
                    {
                        bestMove = { i, j };
                        bestValue = moveValue;
                    }
                }
            }
        }
        printf("The value of the best Move is : %d\n\n", bestValue);

        return bestMove;
    }
};
