#include "fireball.h"
#include "constants.h"
#include <iostream>

Fireball::Fireball(sf::Texture &tex, float xPos,float yPos){
	sprite.setTexture(tex);
	if(yPos < -38000){
		sprite.setColor(sf::Color::Green);
		velocity.x = -Constants::FAST_FIREBALL_SPEED;
	}
	sprite.setTextureRect(sf::IntRect(737,4,25, 19));
	sprite.setPosition(sf::Vector2f(1640, yPos));
	sprite.setScale(sf::Vector2f(Constants::FIREBALL_SCALE, Constants::FIREBALL_SCALE));
	velocity.x = -Constants::FIREBALL_SPEED;
	
}

Fireball::Fireball(){

}

void Fireball::update(float delta){
	animate(delta);
	float xPos = sprite.getPosition().x;
	float yPos = sprite.getPosition().y;

	sprite.setPosition(sf::Vector2f(xPos + velocity.x * delta, yPos));
}

void Fireball::animate(float delta){
	animationTimer += delta;
	int cycle = Constants::FIREBALL_ANIM;
	int phase = animationTimer % cycle;
	phase /= 250;
	if(phase == 0) sprite.setTextureRect(sf::IntRect(737,4,25, 19));
	else if(phase == 1) sprite.setTextureRect(sf::IntRect(769,6,24, 17));
	else if(phase == 2) sprite.setTextureRect(sf::IntRect(737,37,22, 18));
	else if(phase == 3) sprite.setTextureRect(sf::IntRect(769,37,23, 18));
	if(animationTimer > 10000000) animationTimer = 0;

}

void Fireball::destroy(){

}

Fireball::~Fireball(){

}

