#pragma once
#include <SFML/Graphics.hpp>

class Entity{
public:
	Entity(sf::Texture &tex){
		setTexture(tex);
		sf::Sprite sprite;
		sprite.setTexture(*masterTexture);
	}

	Entity();
	~Entity();
	void move(float x, float y);
	void jump();
	void loseHP();
	void die();
	void setTexture(sf::Texture &tex);

private:
	
	int hitPoints;
	sf::Sprite sprite;
	sf::Texture * masterTexture;
	
};