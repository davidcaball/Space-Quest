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
	//checks collision with a single platform and returns true if they collide
	bool checkPlatformCollision(sf::Sprite object);

	//checks collision of all platforms in a vector, returns index of platform
	//that is being collided with
	int checkPlatformVectorCollision(std::vector<sf::Sprite*> platforms);
	sf::Sprite getSprite();

	sf::Sprite sprite;

protected:

	float moveSpeed;
	float acceleration;
	int hitPoints;
	sf::Texture * masterTexture;
	sf::Vector2f velocity;
	
};