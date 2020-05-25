#pragma once
#include <algorithm>
#include <iostream>
#include "Board.h"
#include "BotPlayer.h"

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

    int evaluateSequence(int botMarksNumber, int playerMarksNumber)
    {
        //std::cout << "bot marks= " << botMarksNumber << "player marks = " << playerMarksNumber << "\n";
        if (botMarksNumber == currentBoard->winningLineLength)
            return 10000000;
        else if (botMarksNumber == currentBoard->winningLineLength - 1 && playerMarksNumber == 0)
            return 500000;
        else if (playerMarksNumber == currentBoard->winningLineLength - 1 && botMarksNumber > 0)
            return 700000;
        else if (playerMarksNumber == currentBoard->winningLineLength - 2 && botMarksNumber > 0)
            return 1000;
        return botMarksNumber * 200; //- 100 * playerMarksNumber;
    }
    
    int countSequences(char botMark, char playerMark)
    {
        //char botMark = bot.botMark;
        //char playerMark = bot.playerMark;
        int botMarksCounter = 0;
        int playerMarksCounter = 0;
        int smallerRange = currentBoard->boardSize - currentBoard->winningLineLength + 1;
        int sequencesValue = 0;
        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                botMarksCounter = 0;
                playerMarksCounter = 0;
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j] == botMark)
                        botMarksCounter++;
                    else if (currentBoard->board[i + k][j] == playerMark)
                        playerMarksCounter++;
                }
                sequencesValue += evaluateSequence(botMarksCounter, playerMarksCounter);
            }
        }

        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < smallerRange; ++j)
            {
                botMarksCounter = 0;
                playerMarksCounter = 0;
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i][j + k] == botMark)
                        botMarksCounter++;
                    else if (currentBoard->board[i][j + k] == playerMark)
                        playerMarksCounter++;
                }
                sequencesValue += evaluateSequence(botMarksCounter, playerMarksCounter);
            }
        }

        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = 0; j < smallerRange; ++j)
            {
                botMarksCounter = 0;
                playerMarksCounter = 0;
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j + k] == botMark)
                        botMarksCounter++;
                    else if (currentBoard->board[i + k][j + k] == playerMark)
                        playerMarksCounter++;
                }
                sequencesValue += evaluateSequence(botMarksCounter, playerMarksCounter);
            }
        }

        for (int i = 0; i < smallerRange; ++i)
        {
            for (int j = currentBoard->winningLineLength - 1; j < currentBoard->boardSize; ++j)
            {
                botMarksCounter = 0;
                playerMarksCounter = 0;
                for (int k = 0; k < currentBoard->winningLineLength; ++k)
                {
                    if (currentBoard->board[i + k][j - k] == botMark)
                        botMarksCounter++;
                    else if (currentBoard->board[i + k][j - k] == playerMark)
                        playerMarksCounter++;
                }
                sequencesValue += evaluateSequence(botMarksCounter, playerMarksCounter);
            }
        }
        //std::cout << sequencesValue << std::endl;
        return sequencesValue;
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

    int evaluate(Board* currentBoard, char botMark, char playerMark)
    {
        return countSequences(botMark, playerMark) - countSequences(playerMark, botMark);
    }

    int miniMax(Board* currentBoard, int depth, int alpha, int beta, bool isMax)
    {
        if (isWon('X'))
            return evaluate(currentBoard, bot.botMark, bot.playerMark);
        if (isWon('O'))
            return evaluate(currentBoard, bot.botMark, bot.playerMark);
        if (isDraw())
            return 0;
        if (depth == 0)
        {
           return evaluate(currentBoard, bot.botMark, bot.playerMark);
        }
        if (isMax)
        {
            int best = -100000000;
            for (int i = 0; i < currentBoard->boardSize; ++i)
            {
                for (int j = 0; j < currentBoard->boardSize; ++j)
                {
                    if (currentBoard->board[i][j] == ' ')
                    {
                        currentBoard->board[i][j] = bot.botMark;
                        currentNumberOfMarks++;
                        int eval = miniMax(currentBoard, depth - 1, alpha, beta, false);
                        //currentBoard->print();
                        //std::cout << "Wynik dla maxa " << eval << "\n";
                        best = std::max(best, eval);
                        alpha = std::max(alpha, eval);
                        currentBoard->board[i][j] = ' ';
                        currentNumberOfMarks--;
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return best;
        }
        else
        {
            int best = 100000000;
            for (int i = 0; i < currentBoard->boardSize; ++i)
            {
                for (int j = 0; j < currentBoard->boardSize; ++j)
                {
                    if (currentBoard->board[i][j] == ' ')
                    {
                        currentBoard->board[i][j] = bot.playerMark;
                        currentNumberOfMarks++;
                        int eval = miniMax(currentBoard, depth - 1, alpha, beta, true);
                        //currentBoard->print();
                        //std::cout << "Wynik dla mina " << eval << "\n";
                        best = std::min(best, eval);
                        beta = std::min(beta, eval);
                        currentBoard->board[i][j] = ' ';
                        currentNumberOfMarks--;
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
        int bestValue = -1000000000;
        std::pair<int, int> bestMove = {-1, -1};
        int moveValue = 0;
        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                if (currentBoard->board[i][j] == ' ')
                {
                    currentBoard->board[i][j] = bot.botMark;
                    currentNumberOfMarks++;
                    int depth = 1.5 * currentBoard->boardSize - currentBoard->winningLineLength;
                    moveValue = miniMax(currentBoard, depth, -1000000000, 1000000000, false);
                    std::cout << "move = " << i << ", " << j << " ";
                    std::cout << "value = " << moveValue << "\n";
                    currentBoard->board[i][j] = ' ';
                    currentNumberOfMarks--;
                    if (moveValue > bestValue)
                    {
                        bestMove = { i, j };
                        bestValue = moveValue;
                    }
                }
            }
        }
        std::cout << "The value of the best Move is : " << bestValue << "\n\n";

        return bestMove;
    }
};
