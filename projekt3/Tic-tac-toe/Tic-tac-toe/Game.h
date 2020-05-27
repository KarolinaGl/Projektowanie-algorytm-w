#pragma once
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include "Board.h"
#include "BotPlayer.h"
using namespace std::this_thread;
using namespace std::chrono_literals;

#define INF 9999999999999;

class Game
{
public:
	Board* currentBoard;
    BotPlayer bot;
	int currentNumberOfMarks = 0;
	int maxNumberOfMarks = 0;
    bool isBotGame;
    bool isBotMove = true;

    Game() {}

    Game(Board* currentBoard, bool isBotGame);

    bool isWon(char mark);

    long long evaluateSequence(int botMarksNumber, int playerMarksNumber);
    
    long long countSequences(char botMark, char playerMark);

    bool isDraw()
    {
        return currentNumberOfMarks == maxNumberOfMarks;
    }

    void makeBotMove();

    void fieldClicked(int row, int column);

    long long evaluate(Board* currentBoard, char botMark, char playerMark)
    {
        return countSequences(botMark, playerMark) - countSequences(playerMark, botMark);
    }

    long long miniMax(Board* currentBoard, int depth, long long alpha, long long beta, bool isMax);

    std::pair<int, int> findBestMove();
};
