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
	void setMoveSpeed(float speed);
	float getMoveSpeed();
	sf::Sprite getSprite();
	void setVelocity(sf::Vector2f velocityArg);

	sf::Sprite sprite;

private:

	float moveSpeed;
	int hitPoints;
	sf::Texture * masterTexture;
	sf::Vector2f velocity;
	
};