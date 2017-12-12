#include "snake.h"
#include "constants.h"
#include <iostream>

Snake::Snake(sf::Texture &tex){
	setTexture(tex);
	sf::Sprite sprite;
	animationClock = 0;
}


void Snake::update(float delta){
	animate(delta);
}

void Snake::animate(float delta){
	animationClock+=delta;
	if(animationClock % 800 < 400)
		sprite.setTextureRect(sf::IntRect(3,103, 16, 14));
	else if(animationClock % 800 > 400)
		sprite.setTextureRect(sf::IntRect(34, 103, 18, 14));
	if(animationClock > 10000000) animationClock = 0;
}

Snake::~Snake(){}

