#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>

class Board
{
public:
    std::vector<std::vector<char>> board;

    Board()
    {
        board = {
            {'X', 'O', 'X', ' '},
            {'O', ' ', 'X', 'O'},
            {' ', 'O', 'O', 'X'},
            {' ', 'O', 'X', ' '}
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

int main()
{
    int boardSize = 4;
    Board myBoard;
    myBoard.print();
    unsigned int windowXSize = 500;
    unsigned int windowYSize = 500;
    float boardXSize = 400;
    float boardYSize = 400;
    float boardXOffset = 50;
    float boardYOffset = 50;
    float markXOffset = 10;
    float markYOffset = 10;

    sf::RenderWindow window(sf::VideoMode(windowXSize, windowYSize), "Tic-tac-toe");
    sf::RectangleShape boardRectangle(sf::Vector2f(boardXSize, boardYSize));
    boardRectangle.setPosition(boardXOffset, boardYOffset);
    boardRectangle.setFillColor(sf::Color::Transparent);
    boardRectangle.setOutlineThickness(1);

    std::vector<sf::RectangleShape> gridLines;

    for (int i = 0; i < boardSize; ++i)
    {
        sf::RectangleShape verticalLine(sf::Vector2f(boardYSize, 1));
        verticalLine.rotate(90);
        verticalLine.setPosition(i * boardXSize / boardSize + boardXOffset, boardYOffset);
        gridLines.push_back(verticalLine);
    }    
    for (int i = 0; i < boardSize; ++i)
    {
        sf::RectangleShape horizontalLine(sf::Vector2f(boardXSize, 1));
        horizontalLine.setPosition(boardXOffset, i * boardYSize / boardSize + boardYOffset);
        gridLines.push_back(horizontalLine);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(boardRectangle);

        for (unsigned int i = 0; i < gridLines.size(); ++i)
            window.draw(gridLines[i]);

        for (int i = 0; i < boardSize; ++i)
        {
            for (int j = 0; j < boardSize; ++j)
            {
                if (myBoard.board[i][j] == 'X')
                {
                    sf::RectangleShape crossMark1(sf::Vector2f((boardXSize / boardSize - 2 * markXOffset) * sqrt(2), 1));
                    crossMark1.setPosition(boardXOffset + j * boardXSize / boardSize + markXOffset, boardYOffset + i * boardYSize / boardSize + markYOffset);
                    crossMark1.rotate(45);
                    sf::RectangleShape crossMark2(sf::Vector2f((boardXSize / boardSize - 2 * markXOffset) * sqrt(2), 1));
                    crossMark2.setPosition(boardXOffset + (j + 1) * boardXSize / boardSize - markXOffset, boardYOffset + i * boardYSize / boardSize + markXOffset);
                    crossMark2.rotate(135);
                    window.draw(crossMark1);
                    window.draw(crossMark2);
                }
                if (myBoard.board[i][j] == 'O')
                {
                    sf::CircleShape circleMark(boardXSize / (2 * boardSize) - markXOffset, 50);
                    circleMark.setPosition(boardXOffset + j * boardXSize / boardSize + markXOffset, boardYOffset + i * boardYSize / boardSize + markXOffset);
                    circleMark.setFillColor(sf::Color::Transparent);
                    circleMark.setOutlineThickness(1);
                    window.draw(circleMark);
                }
            }
        }
        window.display();
    }
    return 0;
}
