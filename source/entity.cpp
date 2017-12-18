#include "../headers/entity.h"
#include "../headers/constants.h"
#include "../headers/snake.h"
#include<iostream>
#include <cmath>


Entity::Entity(){

}





// ****************** Setters ******************

void Entity::setTexture(sf::Texture &tex){
	masterTexture = &tex;
}

void Entity::setMoveSpeed(float speed){
	moveSpeed = speed;
}

void Entity::setVelocity(float x, float y){
	velocity.x = x;
	velocity.y = y;
	if(velocity.x > Constants::GENERAL_MAX_VELOCITY)
		velocity.x = Constants::GENERAL_MAX_VELOCITY;
	if(velocity.x < Constants::GENERAL_MAX_VELOCITY * -1)
		velocity.x = Constants::GENERAL_MAX_VELOCITY * -1;
}

void Entity::setAcceleration(float x, float y){
	acceleration.x = x;
	acceleration.y = y;
}





// ****************** Getters ******************

sf::Vector2f Entity::getVelocity(){
	return velocity;
}


sf::Vector2f Entity::getAcceleration(){
	return acceleration;
}


float Entity::getMoveSpeed(){
	return moveSpeed;
}

sf::Sprite * Entity::getSprite(){
	return sprite;
}







//****************** Movement Methods ******************

void Entity::move(float x, float y){
	sprite->setPosition(sprite->getPosition().x + x, sprite->getPosition().y + y);
}


void Entity::jump(){
	velocity.y = Constants::JUMP_SPEED * -1;
}

//Takes a value and a direction and accelarates the entity in that direction
//1 = +X
//-1 = -X
//2 = +Y
//-2 = -Y

void Entity::accelerate(float delta, int direction){
	switch(direction){
		case 1:
			velocity.x += baseAcceleration * delta;
			break;
		case -1:
			velocity.x -= baseAcceleration * delta;
			break;
	};
}

void Entity::update(float delta){
	setVelocity(velocity.x + acceleration.x * delta, velocity.y + acceleration.y * delta);
	sprite->setPosition(sprite->getPosition().x + velocity.x * delta, sprite->getPosition().y + velocity.y * delta);

	//friction
	float temp = getVelocity().x;
	if(getVelocity().x != 0){
		setAcceleration(acceleration.x += Constants::FRICTION * ((velocity.x > 0) ? -1 : 1), acceleration.y);
		//comparison is used to test whether there was a switch in velocity from pos to neg
		//if there is just set velocity to 0 to revent jittering
		if(temp * getVelocity().x < 0) setVelocity(0, getVelocity().y);
	}

	//checks if sprite is below the ground level, corrects if it is.
	//if it is above ground gravity acts on it
	if(sprite->getPosition().y < Constants::WINDOW_HEIGHT - 40){
		setAcceleration(velocity.x, Constants::GRAVITY);
	}else{
			acceleration.y = 0;
			velocity.y = 0;
			sprite->setPosition(sf::Vector2f(sprite->getPosition().x, Constants::WINDOW_HEIGHT - 40));
	}

}


//****************** Collision Methods ******************

//checks collision with a single platform and returns true if they collide
bool Entity::checkPlatformCollision(sf::Sprite object){
	//checking bounds of both object to see if they intersect
	if(object.getPosition().y < sprite->getPosition().y 
		&& object.getPosition().y + object.getLocalBounds().height > sprite->getPosition().y
		&& object.getPosition().x < sprite->getPosition().x
		&& object.getPosition().x + object.getLocalBounds().width + sprite->getLocalBounds().width * 2 > sprite->getPosition().x)
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
bool Entity::checkEntityCollision(Entity * object, float collisionBuffer){
	sf::Vector2f spriteCenter(sprite->getPosition().x - sprite->getOrigin().x + sprite->getLocalBounds().width / 2,
		sprite->getPosition().y - sprite->getOrigin().y + sprite->getLocalBounds().height / 2);
	std::cout << "Sprite loaction " << sprite->getPosition().x << ", " << sprite->getPosition().y << "Snake Location: " << object->getSprite()->getPosition().x << ", " << object->getSprite()->getPosition().y  << std::endl;
	sf::Vector2f objectCenter(object->getSprite()->getPosition().x - object->getSprite()->getOrigin().x + object->getSprite()->getLocalBounds().width / 2,
		object->getSprite()->getPosition().y - object->getSprite()->getOrigin().y + object->getSprite()->getLocalBounds().height / 2);

	float distance = sqrt(pow((spriteCenter.x - objectCenter.x), 2) + pow((spriteCenter.y - objectCenter.y), 2));
	if(distance < collisionBuffer){
		return true;
	}
	return false;
}

//checks collision of a vector of entities, returns index of entity
//that is colliding
int Entity::checkEntityVectorCollision(std::vector<Entity*> objectList, float collisionBuffer){
	for(int i = 0; i < objectList.size(); i++){
		if(checkEntityCollision(objectList[i], collisionBuffer))
			return i;
	}
	return -1;
}

void Entity::loseHP(){

}

void Entity::animate(float delta){
	std::cout << "Entity Animation " << std::endl;
}

Entity::~Entity(){}


