#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>
#include "Board.h"
#include "Window.h"
#include "Button.h"

int main()
{
    bool openSecondWindow = false;
    Board myBoard(5, 3);
    int boardSize = myBoard.boardSize;
    
    unsigned int windowXSize = 600;
    unsigned int windowYSize = 600;
    float boardSizeInPixels = 400;
    float boardXOffset = 50;
    float boardYOffset = 50;
    float markOffset = 15;

    sf::RenderWindow window(sf::VideoMode(windowXSize, windowYSize), "Tic-tac-toe");
    sf::RectangleShape boardRectangle(sf::Vector2f(boardSizeInPixels, boardSizeInPixels));
    boardRectangle.setPosition(boardXOffset, boardYOffset);
    boardRectangle.setFillColor(sf::Color::Transparent);
    boardRectangle.setOutlineThickness(5);
    std::vector<sf::RectangleShape> gridlines;
    std::vector<sf::RectangleShape> verticalGridlines;
    std::vector<sf::RectangleShape> horizontalGridlines;

    Button mybutton(50, 50, 10, 10);

    float textXOffset = 10;
    float textYOffset = 10;
    unsigned int textSize = 50;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;

    sf::Text chooseBoardSize;
    chooseBoardSize.setFont(font);
    chooseBoardSize.setString("Board size:");
    chooseBoardSize.setCharacterSize(textSize);
    chooseBoardSize.setFillColor(sf::Color::Red);
    chooseBoardSize.setStyle(sf::Text::Bold);
    chooseBoardSize.setPosition(textXOffset, textYOffset);

    sf::Text chooseWinningLineLength;
    chooseWinningLineLength.setFont(font);
    chooseWinningLineLength.setString("Winning line length:");
    chooseWinningLineLength.setCharacterSize(textSize);
    chooseWinningLineLength.setFillColor(sf::Color::Red);
    chooseWinningLineLength.setStyle(sf::Text::Bold);
    chooseWinningLineLength.setPosition(textXOffset, 100 + textYOffset);

    initializeGridlines("vertical", gridlines, verticalGridlines, boardSize, boardSizeInPixels, boardXOffset, boardYOffset);
    initializeGridlines("horizontal", gridlines, horizontalGridlines, boardSize, boardSizeInPixels, boardXOffset, boardYOffset);

    int clickCounter = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    openSecondWindow = true;
                    if (openSecondWindow)
                    {
                        if (event.mouseButton.x > boardXOffset && event.mouseButton.x < boardSizeInPixels + boardXOffset
                            && event.mouseButton.y > boardYOffset && event.mouseButton.y < boardSizeInPixels + boardYOffset)
                            handleClick(myBoard, event, clickCounter, verticalGridlines, horizontalGridlines, boardSizeInPixels);
                    }
                }
            }
        }

        window.clear();

        if (!openSecondWindow)
        {
            window.draw(chooseBoardSize);
            window.draw(chooseWinningLineLength);
            mybutton.drawTo(window);
        }

        if (openSecondWindow)
        {
            window.draw(boardRectangle);

            for (unsigned int i = 0; i < gridlines.size(); ++i)
                window.draw(gridlines[i]);

            for (int i = 0; i < boardSize; ++i)
            {
                for (int j = 0; j < boardSize; ++j)
                {
                    if (myBoard.board[i][j] == 'X')
                        drawMark(window, boardSize, boardSizeInPixels, boardXOffset, boardYOffset, markOffset, i, j, 'X');
                    if (myBoard.board[i][j] == 'O')
                        drawMark(window, boardSize, boardSizeInPixels, boardXOffset, boardYOffset, markOffset, i, j, 'O');
                }
            }
        }
        window.display();
    }
    clickCounter = 0;
    
    return 0;
}
