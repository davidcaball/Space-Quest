#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screen.h"

//menu class inherits the screen class and overrids the Run function
class ControlScreen : public Screen{

public:
	ControlScreen(float width, float height, sf::Texture &masterTexture);
	ControlScreen(float width, float height);
	ControlScreen();

	~ControlScreen();

	int Run(sf::RenderWindow &window, float delta);

	void setBackground(sf::Texture &backgroundTexture);

private:


	int selectedItem;
	sf::Sprite background;
};