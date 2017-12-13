#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screen.h"
#include "hero.h"

//menu class inherits the screen class and overrids the Run function
class Game : public Screen{

public:

	Game(float width, float height, sf::Texture &masterTexture);
	~Game();

	int Run(sf::RenderWindow &window, float delta);
	void setBackground();
	void createPlatformVector();
	void updateView();
	void updateBackground();
	Platform * createPlatform(int num);
	Snake createSnake();
	void createSnakeVector();

private:
	bool backgroundChanged;
	float windowHeight;
	float windowWidth;
	sf::View view;
	int selectedItem;
	sf::Font font;
	std::vector<sf::Text*> items;
	sf::Sprite background;
	//music is declared as a pointer as a workaround to not being able to use classes
	//that inherit sf::nonCopyable
	sf::Music * music;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::vector<Platform*> platforms;
	std::vector<Snake*> snakes;
	Hero player;
	sf::Texture * masterTexture;
	sf::Sprite ground;
	sf::Sprite platform;
	Snake snake;
};