#include "platform.h"
#include "constants.h"

Platform::Platform(sf::Texture &tex, float xPos, float yPos){
	sprite.setTexture(tex);
	//sprite.setTextureRect(sf::IntRect(1, 2554, Constants::PLATFORM_WIDTH, 20));
	sprite.setTextureRect(sf::IntRect(730, 64, 100, 20));
	sf::FloatRect newPlatformRect = sprite.getLocalBounds();
	sprite.setOrigin(newPlatformRect.left, newPlatformRect.top);
	sprite.setScale(sf::Vector2f(Constants::PLATFORM_W_SCALE, Constants::PLATFORM_H_SCALE));
	sprite.setPosition(xPos, yPos);
	bool occupied = false;
}

bool Platform::isOccupied(){
	return occupied;
}