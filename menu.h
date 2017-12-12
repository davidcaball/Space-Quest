#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screen.h"

#define MAX_NUMBER_ITEMS 3

//menu class inherits the screen class and overrids the Run function
class Menu : public Screen{

public:

	Menu(float width, float height);
	~Menu();

	int Run(sf::RenderWindow &window, float delta);

	void setBackground(sf::Texture &backgroundTexture);

private:

	int selectedItem;
	sf::Font font;
	sf::Text play;
	sf::Text controls;
	sf::Text title;
	sf::Text exit;
	std::vector<sf::Text*> items;
	sf::Sprite background;
	//music is declared as a pointer as a workaround to not being able to use classes
	//that inherit sf::nonCopyable
	sf::Music * music;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Sprite ground;

};