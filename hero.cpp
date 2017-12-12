#include "hero.h"
#include "constants.h"
#include <iostream>

Hero::Hero(sf::Texture &tex){
	setTexture(tex);
	sf::Sprite sprite;
}

void Hero::setVelocity(sf::Vector2f velocityArg){
	velocity = velocityArg;
	if(velocity.x > Constants::PLAYER_MAX_VELOCITY)
		velocity.x = Constants::PLAYER_MAX_VELOCITY;
	if(velocity.x < Constants::PLAYER_MAX_VELOCITY * -1)
		velocity.x = Constants::PLAYER_MAX_VELOCITY * -1;
}


Hero::~Hero(){}


