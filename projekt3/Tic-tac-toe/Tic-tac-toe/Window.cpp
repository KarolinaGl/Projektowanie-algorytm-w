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

char handleClick(Board& myBoard, sf::Event event, int& clickCounter, std::vector<sf::RectangleShape>& verticalGridlines,
    std::vector<sf::RectangleShape>& horizontalGridlines, float boardSizeInPixels)
{
    int row = 0;
    int column = 0;
    for (int i = 0; i < myBoard.boardSize; ++i)
    { 
        sf::Vector2f verticalLinePosition = verticalGridlines[i].getPosition();
        if (event.mouseButton.x > verticalLinePosition.x && event.mouseButton.x < verticalLinePosition.x + boardSizeInPixels / myBoard.boardSize)
            column = i;
    }
    for (int i = 0; i < myBoard.boardSize; ++i)
    {
        sf::Vector2f horizontalLinePosition = horizontalGridlines[i].getPosition();
        if (event.mouseButton.y > horizontalLinePosition.y && event.mouseButton.y < horizontalLinePosition.y + boardSizeInPixels / myBoard.boardSize)
            row = i;
    }
    if (myBoard.board[row][column] == ' ')
    {
        clickCounter++;
        if (clickCounter % 2 == 0)
        {
            myBoard.board[row][column] = 'O';
            if (isWon(myBoard, 'O'))
                return 'O';
        }
        else
        {
            myBoard.board[row][column] = 'X';
            if (isWon(myBoard, 'X'))
                return 'X';
        }
    }
}

void drawMark(sf::RenderWindow& window, int boardSize, float boardSizeInPixels, float boardXOffset,
    float boardYOffset, float markOffset, int i, int j, char mark)
{
    if (mark == 'X')
    {
        sf::RectangleShape crossMark1(sf::Vector2f((boardSizeInPixels / boardSize - 2 * markOffset) * (float)sqrt(2), 5));
        crossMark1.setPosition(boardXOffset + j * boardSizeInPixels / boardSize + markOffset, boardYOffset + i * boardSizeInPixels / boardSize + markOffset);
        crossMark1.rotate(45);
        sf::RectangleShape crossMark2(sf::Vector2f((boardSizeInPixels / boardSize - 2 * markOffset) * (float)sqrt(2), 5));
        crossMark2.setPosition(boardXOffset + (j + 1) * boardSizeInPixels / boardSize - markOffset, boardYOffset + i * boardSizeInPixels / boardSize + markOffset);
        crossMark2.rotate(135);
        window.draw(crossMark1);
        window.draw(crossMark2);
    }
    else
    {
        sf::CircleShape circleMark(boardSizeInPixels / (2 * boardSize) - markOffset, 50);
        circleMark.setPosition(boardXOffset + j * boardSizeInPixels / boardSize + markOffset, boardYOffset + i * boardSizeInPixels / boardSize + markOffset);
        circleMark.setFillColor(sf::Color::Transparent);
        circleMark.setOutlineThickness(5);
        window.draw(circleMark);
    }
}
