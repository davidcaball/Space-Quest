#include "entity.h"


Entity::Entity(){

}

void Entity::setTexture(sf::Texture &tex){
	masterTexture = &tex;
}

sf::Sprite Entity::getSprite(){
	return sprite;
}


Entity::~Entity(){}


