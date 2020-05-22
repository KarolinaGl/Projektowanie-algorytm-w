#include "Board.h"

Board::Board() {}

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
