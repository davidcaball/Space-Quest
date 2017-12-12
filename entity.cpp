#include "entity.h"
#include "constants.h"


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
	if(velocity.x > Constants::PLAYER_MAX_VELOCITY)
		velocity.x = Constants::PLAYER_MAX_VELOCITY;
	if(velocity.x < Constants::PLAYER_MAX_VELOCITY * -1)
		velocity.x = Constants::PLAYER_MAX_VELOCITY * -1;
}

sf::Vector2f Entity::getVelocity(){
	return velocity;
}

void Entity::setAcceleration(float acc){
	acceleration = acc;
}

float Entity::getAcceleration(){
	return acceleration;
}

void Entity::move(float x, float y){
	sprite.setPosition(sprite.getPosition().x + x, sprite.getPosition().y + y);
}

void Entity::update(float delta){
	sprite.setPosition(sprite.getPosition().x + velocity.x * delta, sprite.getPosition().y + velocity.y * delta);

	//friction
	float temp = getVelocity().x;
	if(getVelocity().x != 0){
		setVelocity(sf::Vector2f(getVelocity().x - Constants::FRICTION * delta * ((getVelocity().x > 0) ? 1 : -1), 
							   	getVelocity().y));
		if(temp * getVelocity().x < 0) setVelocity(sf::Vector2f(0, getVelocity().y));
	}
}

float Entity::getMoveSpeed(){
	return moveSpeed;
}

sf::Sprite Entity::getSprite(){
	return sprite;
}


Entity::~Entity(){}


