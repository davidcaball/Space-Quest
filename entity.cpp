#include "entity.h"


Entity::Entity(){

}

void Entity::setTexture(sf::Texture &tex){
	masterTexture = &tex;
}


Entity::~Entity(){}


