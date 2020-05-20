#pragma once
#include <vector>
#include <iostream>

class Board
{
public:
    std::vector<std::vector<char>> board;
    int boardSize;
    int winningLineLength;

    Board(Board& b)
    {
        board = b.board;
        boardSize = b.boardSize;
        winningLineLength = b.winningLineLength;
    }

    Board(int size, int length)
    {
        board = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };
        winningLineLength = length;
        boardSize = size;
    }

    void print()
    {
        for (unsigned int i = 0; i < board.size(); ++i) {
            for (unsigned int j = 0; j < board[i].size(); ++j)
                std::cout << board[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

bool isWon(Board& currentBoard, char mark);
