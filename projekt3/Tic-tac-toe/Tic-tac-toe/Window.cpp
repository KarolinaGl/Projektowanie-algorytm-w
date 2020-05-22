#include "Window.h"

Window::Window()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Tic-tac-toe");
    view = new MenuView();
}

void initializeGridlines(Board myBoard, std::string direction, std::vector<sf::RectangleShape>& gridlines,
    std::vector<sf::RectangleShape>& directionalGridlines, float boardSizeInPixels, float boardXOffset, float boardYOffset)
{
    for (int i = 0; i <= myBoard.boardSize; ++i)
    {
        sf::RectangleShape line(sf::Vector2f(boardSizeInPixels, 1));
        if (direction == "vertical")
        {
            line.rotate(90);
            line.setPosition(i * boardSizeInPixels / myBoard.boardSize + boardXOffset, boardYOffset);
        }
        else
            line.setPosition(boardXOffset, i * boardSizeInPixels / myBoard.boardSize + boardYOffset);
        gridlines.push_back(line);
        directionalGridlines.push_back(line);
    }
}
