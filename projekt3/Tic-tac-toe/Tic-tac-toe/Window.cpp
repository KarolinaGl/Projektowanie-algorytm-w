#include "Window.h"

Window::Window()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Tic-tac-toe");
    view = new MenuView();
}

void Window::run()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				view->handleEvent(window, this);
		}
		window->clear();

		view->draw(window);

		window->display();

		view->additionalAction(this);

		window->clear();

		view->draw(window);

		window->display();
	}
}
