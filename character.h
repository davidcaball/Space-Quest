#pragma once
#include <SFML/Graphics.hpp>

class Character{
public:

	Chatacter(sf::Texture tex);
	~Character();
	void move(float x, float y);
	void jump();
	void loseHP();

private:
	
	int hitPoints;
	
};