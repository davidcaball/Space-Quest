#include "entity.h"


Entity::Entity(){

}

void Entity::setTexture(sf::Texture &tex){
	masterTexture = &tex;
}

void Entity::setMoveSpeed(float speed){
	moveSpeed = speed;
}

void Entity::setVelocity(sf::Vector2f velocityArg){
	velocity = velocityArg;
}

void Entity::move(float x, float y){
	sprite.setPosition(sprite.getPosition().x + x, sprite.getPosition().y + y);
}

float Entity::getMoveSpeed(){
	return moveSpeed;
}

sf::Sprite Entity::getSprite(){
	return sprite;
}


Entity::~Entity(){}


