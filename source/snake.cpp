#include "../headers/snake.h"
#include "../headers/constants.h"
#include <iostream>

Snake::Snake(sf::Texture &tex, Platform * platform){
	home = &platform->sprite;
	setTexture(tex);
	sprite = new sf::Sprite();
	sprite->setTexture(tex);
	sprite->setTextureRect(sf::IntRect(3,103, 16, 14));
	sprite->setOrigin(sprite->getLocalBounds().left + sprite->getLocalBounds().width / 2,
				sprite->getLocalBounds().top + sprite->getLocalBounds().height);
	sprite->setPosition(home->getPosition().x + home->getLocalBounds().width / 2, home->getPosition().y);
	scale = Constants::SNAKE_SCALE;
	sprite->setScale(sf::Vector2f(scale, scale));
	animationClock = 0;
	velocity.x = Constants::SNAKE_SPEED;
	
}

void Snake::update(float delta){
	float xPos = sprite->getPosition().x;
	float yPos = sprite->getPosition().y;

	sprite->setPosition(sf::Vector2f(xPos + velocity.x * delta, yPos));

	animate(delta);
}

void Snake::animate(float delta){
	std::cout << "Snake Animation " << std::endl;
	if(velocity.x > 0) sprite->setScale(sf::Vector2f(scale, scale));
	if(velocity.x < 0) sprite->setScale(sf::Vector2f(-scale, scale));

	animationClock+=delta;
	if(animationClock % 800 < 400)
		sprite->setTextureRect(sf::IntRect(3,103, 16, 14));
	else if(animationClock % 800 > 400)
		sprite->setTextureRect(sf::IntRect(34, 103, 18, 14));
	if(animationClock > 10000000) animationClock = 0;

	if(sprite->getPosition().x > home->getPosition().x 
		+ home->getLocalBounds().width * Constants::PLATFORM_W_SCALE)
		velocity.x = -Constants::SNAKE_SPEED;
	if(sprite->getPosition().x < home->getPosition().x)
		velocity.x = Constants::SNAKE_SPEED;

}

sf::Sprite * Snake::getSprite(){
	return sprite;
}

Snake::~Snake(){}

