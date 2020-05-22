#pragma once
#include <vector>
#include <iostream>

class Board
{
public:
    std::vector<std::vector<char>> board;
    int boardSize;
    int winningLineLength;

    Board();

    Board(int size, int length);

    void print();
};
