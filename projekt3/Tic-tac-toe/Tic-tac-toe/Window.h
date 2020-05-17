#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"

void initializeGridlines(std::string direction, std::vector<sf::RectangleShape>& gridlines, std::vector<sf::RectangleShape>& directionalGridlines, int boardSize, float boardSizeInPixels, float boardXOffset, float boardYOffset);

void handleClick(Board& myBoard, sf::Event event, int& clickCounter, std::vector<sf::RectangleShape>& verticalGridlines, std::vector<sf::RectangleShape>& horizontalGridlines, float boardSizeInPixels);

void drawMark(sf::RenderWindow& window, int boardSize, float boardSizeInPixels, float boardXOffset, float boardYOffset, float markOffset, int i, int j, char mark);


