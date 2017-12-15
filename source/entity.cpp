#include "../headers/entity.h"
#include "../headers/constants.h"
#include<iostream>
#include <cmath>


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
	if(velocity.x > Constants::GENERAL_MAX_VELOCITY)
		velocity.x = Constants::GENERAL_MAX_VELOCITY;
	if(velocity.x < Constants::GENERAL_MAX_VELOCITY * -1)
		velocity.x = Constants::GENERAL_MAX_VELOCITY * -1;
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
	setVelocity(sf::Vector2f(velocity.x, velocity.y));
	sprite.setPosition(sprite.getPosition().x + velocity.x * delta, sprite.getPosition().y + velocity.y * delta);

	//friction
	float temp = getVelocity().x;
	if(getVelocity().x != 0){
		setVelocity(sf::Vector2f(getVelocity().x - Constants::FRICTION * delta * ((getVelocity().x > 0) ? 1 : -1), 
							   	getVelocity().y));
		//comparison is used to test whether there was a switch in velocity from pos to neg
		//if there is just set velocity to 0 to revent jittering
		if(temp * getVelocity().x < 0) setVelocity(sf::Vector2f(0, getVelocity().y));
	}

	//checks if sprite is below the ground level, corrects if it is.
	//if it is above ground gravity acts on it
	if(sprite.getPosition().y < Constants::WINDOW_HEIGHT - 40){
		setVelocity(sf::Vector2f(velocity.x, velocity.y + Constants::GRAVITY * delta));
	}else{
			velocity.y = 0;
			sprite.setPosition(sf::Vector2f(sprite.getPosition().x, Constants::WINDOW_HEIGHT - 40));
	}

}

float Entity::getMoveSpeed(){
	return moveSpeed;
}

sf::Sprite Entity::getSprite(){
	return sprite;
}

void Entity::jump(){
	velocity.y = Constants::JUMP_SPEED * -1;
}

//checks collision with a single platform and returns true if they collide
bool Entity::checkPlatformCollision(sf::Sprite object){
	//checking bounds of both object to see if they intersect
	if(object.getPosition().y < sprite.getPosition().y 
		&& object.getPosition().y + object.getLocalBounds().height > sprite.getPosition().y
		&& object.getPosition().x < sprite.getPosition().x
		&& object.getPosition().x + object.getLocalBounds().width + sprite.getLocalBounds().width * 2 > sprite.getPosition().x)
		return true;

}

//checks collision of all platforms in a vector, returns index of platform
//that is being collided with
int Entity::checkPlatformVectorCollision(std::vector<Platform*> platforms){
	for(int i = 0; i < platforms.size(); i++){
		if(checkPlatformCollision(platforms[i]->sprite)) return i;
	}
	return -1;
}

//checks collision between two entities
bool Entity::checkEntityCollision(Entity object){
	sf::Vector2f spriteCenter(sprite.getPosition().x - sprite.getOrigin().x + sprite.getLocalBounds().width / 2,
		sprite.getPosition().y - sprite.getOrigin().y + sprite.getLocalBounds().height / 2);

	sf::Vector2f objectCenter(object.sprite.getPosition().x - object.sprite.getOrigin().x + object.sprite.getLocalBounds().width / 2,
		object.sprite.getPosition().y - object.sprite.getOrigin().y + object.sprite.getLocalBounds().height / 2);

	float distance = sqrt(pow((spriteCenter.x - objectCenter.x), 2) + pow((spriteCenter.y - objectCenter.y), 2));
	
	if(distance < Constants::COLLISION_BUFFER){
		return true;
	}
	return false;
}

//checks collision of a vector of entities, returns index of entity
//that is colliding
int Entity::checkEntityVectorCollision(std::vector<Entity*> objectList){
	for(int i = 0; i < objectList.size(); i++){
		if(checkEntityCollision(*objectList[i]))
			return i;
	}
	return -1;
}

void Entity::loseHP(){

}

void Entity::animate(){

}

Entity::~Entity(){}


