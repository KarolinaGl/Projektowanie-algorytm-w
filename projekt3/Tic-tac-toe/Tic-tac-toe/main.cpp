#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>
#include <string>
#include "Board.h"
#include "Window.h"
#include "Button.h"


int main()
{
    int boardSizeNumber = 7;
    int winningLineLengthNumber = 3;
    bool openSecondWindow = false;
    Board myBoard(4, 3);
    int boardSize = myBoard.boardSize;
    
    unsigned int windowXSize = 600;
    unsigned int windowYSize = 600;
    float boardSizeInPixels = 500;
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

    float textXOffset = 10;
    float textYOffset = 10;
    unsigned int textSize = 40;
    int line1Height = 50;
    int line2Height = 150;
    int line3Height = 250;
    int line4Height = 350;
    int line5Height = 450;
    int squareButtonSize = 50;
    int submitButtonWidth = 200;
    
    initializeGridlines(myBoard, "vertical", gridlines, verticalGridlines, boardSizeInPixels, boardXOffset, boardYOffset);
    initializeGridlines(myBoard, "horizontal", gridlines, horizontalGridlines, boardSizeInPixels, boardXOffset, boardYOffset);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text chooseBoardSize;
    chooseBoardSize.setFont(font);
    chooseBoardSize.setString("Board size:");
    chooseBoardSize.setCharacterSize(textSize);
    chooseBoardSize.setFillColor(sf::Color::White);
    chooseBoardSize.setStyle(sf::Text::Bold);
    chooseBoardSize.setPosition(windowXSize / 2 - chooseBoardSize.getLocalBounds().width / 2, line1Height);
   
    Button boardSizeMinusButton(squareButtonSize, squareButtonSize, "-");
    boardSizeMinusButton.setButtonPosition(windowXSize / 3, line2Height);
    boardSizeMinusButton.setTextPosition(windowXSize / 3 + 8, line2Height - 8);
    boardSizeMinusButton.setCharacterSize(70);
    boardSizeMinusButton.setTextColor(sf::Color::Black);

    sf::Text boardSizeText;
    boardSizeText.setFont(font);
    boardSizeText.setString(std::to_string(boardSizeNumber));
    boardSizeText.setCharacterSize(textSize);
    boardSizeText.setFillColor(sf::Color::White);
    boardSizeText.setStyle(sf::Text::Bold);
    boardSizeText.setPosition(windowXSize / 2 - boardSizeText.getLocalBounds().width / 2, line2Height);

    Button boardSizePlusButton(squareButtonSize, squareButtonSize, "+");
    boardSizePlusButton.setButtonPosition(windowXSize * 2 / 3 - squareButtonSize, line2Height);
    boardSizePlusButton.setTextPosition(windowXSize * 2 / 3 - squareButtonSize, line2Height);
    boardSizePlusButton.setCharacterSize(70);
    boardSizePlusButton.setTextColor(sf::Color::Black);

    sf::Text chooseWinningLineLength;
    chooseWinningLineLength.setFont(font);
    chooseWinningLineLength.setString("Winning line length:");
    chooseWinningLineLength.setCharacterSize(textSize);
    chooseWinningLineLength.setFillColor(sf::Color::White);
    chooseWinningLineLength.setStyle(sf::Text::Bold);
    chooseWinningLineLength.setPosition(windowXSize / 2 - chooseWinningLineLength.getLocalBounds().width / 2, line3Height);

    Button winningLineLengthMinusButton(squareButtonSize, squareButtonSize, "-");
    winningLineLengthMinusButton.setButtonPosition(windowXSize / 3, line4Height);
    winningLineLengthMinusButton.setTextPosition(windowXSize / 3 + 8, line4Height - 8);
    winningLineLengthMinusButton.setCharacterSize(70);
    winningLineLengthMinusButton.setTextColor(sf::Color::Black);

    sf::Text winningLineLengthText;
    winningLineLengthText.setFont(font);
    winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
    winningLineLengthText.setCharacterSize(textSize);
    winningLineLengthText.setFillColor(sf::Color::White);
    winningLineLengthText.setStyle(sf::Text::Bold);
    winningLineLengthText.setPosition(windowXSize / 2 - boardSizeText.getLocalBounds().width / 2, line4Height);

    Button winningLineLengthPlusButton(squareButtonSize, squareButtonSize, "+");
    winningLineLengthPlusButton.setButtonPosition(windowXSize * 2 / 3 - squareButtonSize, line4Height);
    winningLineLengthPlusButton.setTextPosition(windowXSize * 2 / 3 - squareButtonSize, line4Height);
    winningLineLengthPlusButton.setCharacterSize(70);
    winningLineLengthPlusButton.setTextColor(sf::Color::Black);

    Button submitButton(submitButtonWidth, 100, "Submit");
    submitButton.setButtonPosition(windowXSize / 2 - submitButtonWidth / 2, line5Height);
    submitButton.setTextPosition(windowXSize / 2 - submitButtonWidth / 2 + 30, line5Height + 40);
    submitButton.setCharacterSize(textSize);
    submitButton.setTextColor(sf::Color::Black);


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
                    if (boardSizeMinusButton.isMouseOver(window))
                    {
                        if (boardSizeNumber >= 4)
                        {
                            boardSizeNumber--;
                            boardSizeText.setString(std::to_string(boardSizeNumber));
                            boardSizeText.setPosition(windowXSize / 2 - boardSizeText.getLocalBounds().width / 2, line2Height);
                        }
                    }
                    if (boardSizePlusButton.isMouseOver(window))
                    {
                        boardSizeNumber++;
                        boardSizeText.setString(std::to_string(boardSizeNumber));
                        boardSizeText.setPosition(windowXSize / 2 - boardSizeText.getLocalBounds().width / 2, line2Height);
                    }

                    if (winningLineLengthMinusButton.isMouseOver(window))
                    {
                        if (winningLineLengthNumber >= 4)
                        {
                            winningLineLengthNumber--;
                            winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
                            winningLineLengthText.setPosition(windowXSize / 2 - winningLineLengthText.getLocalBounds().width / 2, line4Height);
                        }
                    }
                    if (winningLineLengthPlusButton.isMouseOver(window))
                    {
                        if (winningLineLengthNumber < boardSizeNumber)
                        {
                            winningLineLengthNumber++;
                            winningLineLengthText.setString(std::to_string(winningLineLengthNumber));
                            winningLineLengthText.setPosition(windowXSize / 2 - winningLineLengthText.getLocalBounds().width / 2, line4Height);
                        }
                    }

                    if (submitButton.isMouseOver(window))
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
            boardSizePlusButton.draw(window);
            boardSizeMinusButton.draw(window);
            winningLineLengthPlusButton.draw(window);
            winningLineLengthMinusButton.draw(window);
            submitButton.draw(window);
            window.draw(boardSizeText);
            window.draw(winningLineLengthText);
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    std::cout << "x= " << position.x << "y= " << position.y << std::endl;
                }
            }
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
