#include "Window.h"

Window::Window()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Tic-tac-toe");
    view = new MenuView();
}

