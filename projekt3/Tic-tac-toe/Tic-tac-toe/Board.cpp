#include "Board.h"

Board::Board(int size, int length)
{
    boardSize = size;
    winningLineLength = length;
    for (int i = 0; i < boardSize; i++) {
        std::vector<char> rows;
        for (int j = 0; j < boardSize; j++)
            rows.push_back(' ');
        board.push_back(rows);
    }
}

void Board::print()
{
    for (unsigned int i = 0; i < board.size(); ++i) {
        for (unsigned int j = 0; j < board[i].size(); ++j)
            std::cout << board[i][j] << " ";
        std::cout << std::endl;
    }
}

bool isWon(Board& currentBoard, char mark)
{
    int sameMarksCounter = 0;
    int smallerRange = currentBoard.boardSize - currentBoard.winningLineLength + 1;
    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = 0; j < currentBoard.boardSize; ++j)
        {
            for (int k = 0; k < currentBoard.winningLineLength; ++k)
            {
                if (currentBoard.board[i + k][j] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard.winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }

    for (int i = 0; i < currentBoard.boardSize; ++i)
    {
        for (int j = 0; j < smallerRange; ++j)
        {
            for (int k = 0; k < currentBoard.winningLineLength; ++k)
            {
                if (currentBoard.board[i][j + k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard.winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }

    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = 0; j < smallerRange; ++j)
        {
            for (int k = 0; k < currentBoard.winningLineLength; ++k)
            {
                if (currentBoard.board[i + k][j + k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard.winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }

    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = currentBoard.winningLineLength - 1; j < currentBoard.boardSize; ++j)
        {
            for (int k = 0; k < currentBoard.winningLineLength; ++k)
            {
                if (currentBoard.board[i + k][j - k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard.winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }
    return false;
}
