#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Button.h"
#include "View.h"
#include "MenuView.h"
#include "GameView.h"
#include "Constants.h"


class Window
{
public:
	View* view;
	sf::RenderWindow* window;

	Window();

	void run()
	{
		while (window->isOpen())
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					view->handleEvent(window, this);
				}
			}
			window->clear();

			view->draw(window);

			window->display();
		}
	}

	void changeView(View* newView)
	{
		delete view;
		view = newView;
	}
};

void initializeGridlines(Board myBoard, std::string direction, std::vector<sf::RectangleShape>& gridlines, std::vector<sf::RectangleShape>& directionalGridlines, float boardSizeInPixels, float boardXOffset, float boardYOffset);

char handleClick(Board& myBoard, sf::Event event, int& clickCounter, std::vector<sf::RectangleShape>& verticalGridlines, std::vector<sf::RectangleShape>& horizontalGridlines, float boardSizeInPixels);
