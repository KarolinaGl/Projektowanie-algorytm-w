#include "GameView.h"
#include "Window.h"

GameView::GameView(int boardSizeNumber, int winningLineLengthNumber, bool isBotGame)
{
    this->boardSizeNumber = boardSizeNumber;
    this->winningLineLengthNumber = winningLineLengthNumber;
    initBoard();
    initBoardRectangle();
    initWhoseTurnText();
    initGridlines("vertical", verticalGridlines);
    initGridlines("horizontal", horizontalGridlines);
    this->game = Game(&currentBoard, isBotGame);
}

void GameView::handleEvent(sf::RenderWindow* renderWindow, Window* window)
{
    int row = -1;
    int column = -1;
    for (int i = 0; i < currentBoard.boardSize; ++i)
    {
        sf::Vector2f verticalLinePosition = verticalGridlines[i].getPosition();
        if (sf::Mouse::getPosition(*renderWindow).x >= verticalLinePosition.x &&
            sf::Mouse::getPosition(*renderWindow).x < verticalLinePosition.x + BOARD_SIZE_IN_PIXELS / currentBoard.boardSize)
            column = i;
    }
    for (int i = 0; i < currentBoard.boardSize; ++i)
    {
        sf::Vector2f horizontalLinePosition = horizontalGridlines[i].getPosition();
        if (sf::Mouse::getPosition(*renderWindow).y >= horizontalLinePosition.y &&
            sf::Mouse::getPosition(*renderWindow).y < horizontalLinePosition.y + BOARD_SIZE_IN_PIXELS / currentBoard.boardSize)
            row = i;
    }

    game.fieldClicked(row, column); 

    if (currentBoard.board[row][column] == 'X')
        whoseTurnText.setString("O player's turn");
    else if (currentBoard.board[row][column] == 'O')
        whoseTurnText.setString("X player's turn");

    if (isGameFinished(window))
    {
        whoseTurnText.setString("");
        return;
    }
}

void GameView::draw(sf::RenderWindow* window)
{
    window->draw(whoseTurnText);

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
    float gridlineSpacing = (float) BOARD_SIZE_IN_PIXELS / boardSizeNumber;
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
            line.setPosition(i * (float) BOARD_SIZE_IN_PIXELS / boardSizeNumber + BOARD_X_OFFSET, BOARD_Y_OFFSET);
        }
        else
            line.setPosition(BOARD_X_OFFSET, i * (float) BOARD_SIZE_IN_PIXELS / boardSizeNumber + BOARD_Y_OFFSET);
        gridlines.push_back(line);
        directionalGridlines.push_back(line);
    }
}

bool GameView::isGameFinished(Window* window)
{
    if (game.isWon('O'))
        return true;
    else if (game.isWon('X'))
        return true;
    else if (game.isDraw())
        return true;
    return false;
}

void GameView::switchWindow(Window* window)
{
    if (game.isWon('O'))
    {
        whoseTurnText.setString("");
        draw(window->window);
        ScoreView* scoreView = new ScoreView("O");
        window->changeView(scoreView);
    }
    else if (game.isWon('X'))
    {
        whoseTurnText.setString("");
        draw(window->window);
        ScoreView* scoreView = new ScoreView("X");
        window->changeView(scoreView);
    }
    else if (game.isDraw())
    {        
        whoseTurnText.setString("");
        draw(window->window);
        ScoreView* scoreView = new ScoreView(" ");
        window->changeView(scoreView);
    }
}

void GameView::additionalAction(Window* window)
{
    if (isGameFinished(window)) {
        whoseTurnText.setString("");
        sleep_for(2s);
        switchWindow(window);
        return;
    }
    if (game.isBotGame)
    {
        whoseTurnText.setString("X player's turn");
        game.makeBotMove();
        whoseTurnText.setString("O player's turn");
    }
}

void GameView::initWhoseTurnText()
{
    font.loadFromFile("arial.ttf");
    whoseTurnText.setFont(font);
    whoseTurnText.setCharacterSize(TEXT_SIZE);
    whoseTurnText.setString("X player's turn");
    whoseTurnText.setFillColor(sf::Color::White);
    whoseTurnText.setStyle(sf::Text::Bold);
    whoseTurnText.setPosition(WINDOW_X_SIZE / 2 - whoseTurnText.getLocalBounds().width / 2, LINE_6_HEIGHT);
}
