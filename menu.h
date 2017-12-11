#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_ITEMS 3

class Menu{

public:

	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void setBackground(sf::Texture &backgroundTexture);

private:

	int selectedItem;
	sf::Font font;
	sf::Text play;
	sf::Sprite background;

};