#include "GameView.h"
#include "Window.h"

void GameView::handleEvent(sf::RenderWindow* renderWindow, Window* window)
{
    int row = -1;
    int column = -1;
    for (int i = 0; i < currentBoard.boardSize; ++i)
    {
        sf::Vector2f verticalLinePosition = verticalGridlines[i].getPosition();
        if (sf::Mouse::getPosition(*renderWindow).x >= verticalLinePosition.x && sf::Mouse::getPosition(*renderWindow).x < verticalLinePosition.x + BOARD_SIZE_IN_PIXELS / currentBoard.boardSize)
            column = i;
    }
    for (int i = 0; i < currentBoard.boardSize; ++i)
    {
        sf::Vector2f horizontalLinePosition = horizontalGridlines[i].getPosition();
        if (sf::Mouse::getPosition(*renderWindow).y >= horizontalLinePosition.y && sf::Mouse::getPosition(*renderWindow).y < horizontalLinePosition.y + BOARD_SIZE_IN_PIXELS / currentBoard.boardSize)
            row = i;
    }


    if (row != -1 && column != -1 && currentBoard.board[row][column] == ' ')
    {
        clickCounter++;
        if (clickCounter % 2 == 0)
        {
            currentBoard.board[row][column] = 'O';
            if (game.isWon('O'))
            {
                std::cout << "O won\n";
                ScoreView* scoreView = new ScoreView("O");
                window->changeView(scoreView);
                return;
            }
        }
        else
        {
            currentBoard.board[row][column] = 'X';
            if (game.isWon('X'))
            {
                std::cout << "X won\n";
                ScoreView* scoreView = new ScoreView("X");
                window->changeView(scoreView);
                return;
            }
        }
        if (game.isDraw())
        {
            std::cout << "Draw\n";
            ScoreView* scoreView = new ScoreView(" ");
            window->changeView(scoreView);
        }
    }
}

void GameView::draw(sf::RenderWindow* window)
{
	window->draw(boardRectangle);
    for (unsigned int i = 0; i < gridlines.size(); ++i)
        window->draw(gridlines[i]);
    for (int i = 0; i < boardSizeNumber; ++i)
    {
        for (int j = 0; j < boardSizeNumber; ++j)
            drawMark(*window, i, j, currentBoard.board[i][j]);
    }
}

void GameView::drawMark(sf::RenderWindow& window, int i, int j, char mark)
{
    float gridlineSpacing = BOARD_SIZE_IN_PIXELS / boardSizeNumber;
    if (mark == 'X')
    {
        sf::RectangleShape crossMark1(sf::Vector2f((gridlineSpacing - 2 * MARK_OFFSET) * (float)sqrt(2), 5));
        crossMark1.setPosition(BOARD_X_OFFSET + j * gridlineSpacing + MARK_OFFSET, BOARD_Y_OFFSET + i * gridlineSpacing + MARK_OFFSET);
        crossMark1.rotate(45);
        sf::RectangleShape crossMark2(sf::Vector2f((gridlineSpacing - 2 * MARK_OFFSET) * (float)sqrt(2), 5));
        crossMark2.setPosition(BOARD_X_OFFSET + (j + 1) * gridlineSpacing - MARK_OFFSET, BOARD_Y_OFFSET + i * gridlineSpacing + MARK_OFFSET);
        crossMark2.rotate(135);
        window.draw(crossMark1);
        window.draw(crossMark2);
    }
    else if (mark == 'O')
    {
        sf::CircleShape circleMark(gridlineSpacing / 2 - MARK_OFFSET, 50);
        circleMark.setPosition(BOARD_X_OFFSET + j * gridlineSpacing + MARK_OFFSET, BOARD_Y_OFFSET + i * gridlineSpacing + MARK_OFFSET);
        circleMark.setFillColor(sf::Color::Transparent);
        circleMark.setOutlineThickness(5);
        window.draw(circleMark);
    }
}

void GameView::initBoard()
{
    currentBoard = Board(boardSizeNumber, winningLineLengthNumber);
}

void GameView::initBoardRectangle()
{
	boardRectangle.setPosition(BOARD_X_OFFSET, BOARD_Y_OFFSET);
	boardRectangle.setFillColor(sf::Color::Transparent);
	boardRectangle.setOutlineThickness(5);
}

void GameView::initGridlines(std::string direction, std::vector<sf::RectangleShape>& directionalGridlines)
{
    for (int i = 0; i <= boardSizeNumber; ++i)
    {
        sf::RectangleShape line(sf::Vector2f(BOARD_SIZE_IN_PIXELS, 1));
        if (direction == "vertical")
        {
            line.rotate(90);
            line.setPosition(i * BOARD_SIZE_IN_PIXELS / boardSizeNumber + BOARD_X_OFFSET, BOARD_Y_OFFSET);
        }
        else
            line.setPosition(BOARD_X_OFFSET, i * BOARD_SIZE_IN_PIXELS / boardSizeNumber + BOARD_Y_OFFSET);
        gridlines.push_back(line);
        directionalGridlines.push_back(line);
    }
}
