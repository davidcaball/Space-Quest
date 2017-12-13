#pragma once
#include "platform.h"
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
	void update(float delta);
	void move(float x, float y);
	void jump();
	void loseHP();
	void die();
	void setTexture(sf::Texture &tex);
	void setMoveSpeed(float speed);
	float getMoveSpeed();
	void setVelocity(sf::Vector2f velocityArg);
	sf::Vector2f getVelocity();
	void setAcceleration(float acc);
	float getAcceleration();
	
	bool checkPlatformCollision(sf::Sprite object);


	int checkPlatformVectorCollision(std::vector<Platform*> platforms);
	
	bool checkEntityCollision(Entity object);

	int checkEntityVectorCollision(std::vector<Entity*> objectList);
	sf::Sprite getSprite();

	sf::Sprite sprite;

protected:

	float moveSpeed;
	float acceleration;
	int hitPoints;
	sf::Texture * masterTexture;
	sf::Vector2f velocity;
	
};