#include "Game.h"

Game::Game(Board* currentBoard, bool isBotGame)
{
    this->currentBoard = currentBoard;
    maxNumberOfMarks = currentBoard->boardSize * currentBoard->boardSize;
    this->isBotGame = isBotGame;
    bot = BotPlayer(currentBoard);
    if (isBotGame)
        makeBotMove();
}

bool Game::isWon(char mark)
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

long long Game::evaluateSequence(int botMarksNumber, int playerMarksNumber)
{
    if (botMarksNumber == currentBoard->winningLineLength)
        return INF;
    for (int i = 1; i < currentBoard->winningLineLength - 1; ++i)
    {
        if (playerMarksNumber == currentBoard->winningLineLength - i && botMarksNumber > 0)
            return 7000000 / i;
    }
    for (int i = 1; i < currentBoard->winningLineLength - 1; ++i)
    {
        if (botMarksNumber == currentBoard->winningLineLength - i && playerMarksNumber == 0)
            return 500000 / i;
    }
    return botMarksNumber;
}

long long Game::countSequences(char botMark, char playerMark)
{
    int botMarksCounter = 0;
    int playerMarksCounter = 0;
    int smallerRange = currentBoard->boardSize - currentBoard->winningLineLength + 1;
    long long sequencesValue = 0;
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
    return sequencesValue;
}

void Game::makeBotMove()
{
    if (isBotMove)
    {
        std::pair<int, int> rowAndColumn = findBestMove();
        fieldClicked(rowAndColumn.first, rowAndColumn.second);
    }
}

void Game::fieldClicked(int row, int column)
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

long long Game::miniMax(Board* currentBoard, int depth, long long alpha, long long beta, bool isMax)
{
    if (isWon('X'))
        return evaluate(currentBoard, bot.botMark, bot.playerMark);
    if (isWon('O'))
        return evaluate(currentBoard, bot.botMark, bot.playerMark);
    if (isDraw())
        return 0;
    if (depth == 0)
        return evaluate(currentBoard, bot.botMark, bot.playerMark);
    if (isMax)
    {
        long long best = -INF;
        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                if (currentBoard->board[i][j] == ' ')
                {
                    currentBoard->board[i][j] = bot.botMark;
                    currentNumberOfMarks++;
                    long long eval = miniMax(currentBoard, depth - 1, alpha, beta, false);
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
        long long best = INF;
        for (int i = 0; i < currentBoard->boardSize; ++i)
        {
            for (int j = 0; j < currentBoard->boardSize; ++j)
            {
                if (currentBoard->board[i][j] == ' ')
                {
                    currentBoard->board[i][j] = bot.playerMark;
                    currentNumberOfMarks++;
                    long long eval = miniMax(currentBoard, depth - 1, alpha, beta, true);
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

std::pair<int, int> Game::findBestMove()
{
    long long bestValue = -INF;
    std::pair<int, int> bestMove = { -1, -1 };
    long long moveValue = 0;
    for (int i = 0; i < currentBoard->boardSize; ++i)
    {
        for (int j = 0; j < currentBoard->boardSize; ++j)
        {
            if (currentBoard->board[i][j] == ' ')
            {
                currentBoard->board[i][j] = bot.botMark;
                currentNumberOfMarks++;
                int depth = std::round(15 / currentBoard->boardSize);
                moveValue = miniMax(currentBoard, depth, -9999999999999, 9999999999999, false);
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
    return bestMove;
}
