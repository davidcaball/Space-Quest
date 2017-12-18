#pragma once
#include "entity.h"
#include "constants.h"


class Snake : public Entity{

public:	
	void update(float delta);
	void animate(float delta);
	sf::Sprite * getSprite();
	//flips the sprite left or right
	Snake(sf::Texture &tex, Platform * platform);
	Snake(){}
	~Snake();

private:
	sf::Sprite * sprite;
	float scale;
	long animationClock;
	sf::Sprite * home;

};
