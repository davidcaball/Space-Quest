#pragma once
#include <SFML/Graphics.hpp>
#include "screen.h"

#define MAX_NUMBER_ITEMS 3

//menu class inherits the screen class and overrids the Run function
class Menu : public Screen{

public:

	Menu(float width, float height);
	~Menu();

	int Run(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void setBackground(sf::Texture &backgroundTexture);

private:

	int selectedItem;
	sf::Font font;
	sf::Text play;
	sf::Text controls;
	sf::Text title;
	sf::Sprite background;

};