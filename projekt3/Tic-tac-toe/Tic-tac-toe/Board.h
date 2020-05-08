#pragma once
#include <vector>

class Board
{
public:
    std::vector<std::vector<char>> board;

    Board()
    {
        board = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };
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