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

	virtual void update(float delta);
	virtual void animate(float delta);

	void move(float x, float y);
	
	
	void setTexture(sf::Texture &tex);
	void setMoveSpeed(float speed);
	void setVelocity(float x, float y);
	void setAcceleration(float x, float y);

	float getMoveSpeed();
	sf::Vector2f getAcceleration();
	sf::Vector2f getVelocity();
	virtual sf::Sprite * getSprite();

	void accelerate(float delta, int direction);
	void jump();
	void loseHP();
	void die();
	
	bool checkPlatformCollision(sf::Sprite object);
	int checkPlatformVectorCollision(std::vector<Platform*> platforms);
	bool checkEntityCollision(Entity * object, float collisionBuffer);
	int checkEntityVectorCollision(std::vector<Entity*> objectList, float collisionBuffer);

	int hitPoints;

protected:

	sf::Sprite * sprite;
	float baseAcceleration;
	float moveSpeed;
	sf::Vector2f acceleration;
	
	sf::Texture * masterTexture;
	sf::Vector2f velocity;
	
};