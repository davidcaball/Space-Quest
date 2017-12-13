#include "platform.h"
#include "constants.h"

Platform::Platform(sf::Texture &tex, float xPos, float yPos){
	sprite.setTexture(tex);
	sprite.setTextureRect(sf::IntRect(1, 2554, Constants::PLATFORM_WIDTH, 20));
	sf::FloatRect newPlatformRect = sprite.getLocalBounds();
	sprite.setOrigin(newPlatformRect.left, newPlatformRect.top);
	sprite.setScale(sf::Vector2f(1.0f, 2.0f));
	sprite.setPosition(xPos, yPos);
	bool occupied = false;
}

bool Platform::isOccupied(){
	return occupied;
}