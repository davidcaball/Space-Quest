#pragma once
#include <SFML/Graphics.hpp>

//The screen class is a basic template class that will handle switching
//between different screens such as the menu, the game, and controls
//screen

//The Run() function will render all the necessary elements, and
//also handle user event inputs, it will return a value indicating
//which screen will be rendered next

class Screen{
public:
	virtual int Run(sf::RenderWindow &App) = 0;
};