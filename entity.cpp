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
	sprite.setPosition(sprite.getPosition().x + velocity.x * delta, sprite.getPosition().y + velocity.y * delta);

	//friction
	float temp = getVelocity().x;
	if(getVelocity().x != 0){
		setVelocity(sf::Vector2f(getVelocity().x - Constants::FRICTION * delta * ((getVelocity().x > 0) ? 1 : -1), 
							   	getVelocity().y));
		if(temp * getVelocity().x < 0) setVelocity(sf::Vector2f(0, getVelocity().y));
	}

	if(sprite.getPosition().y < Constants::WINDOW_HEIGHT - 40){
		velocity.y += Constants::GRAVITY * delta;
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

bool Entity::checkPlatformCollision(sf::Sprite object){
	if(object.getPosition().y < sprite.getPosition().y 
		&& object.getPosition().y + object.getLocalBounds().height > sprite.getPosition().y
		&& object.getPosition().x < sprite.getPosition().x
		&& object.getPosition().x + object.getLocalBounds().width + sprite.getLocalBounds().width * 2 > sprite.getPosition().x)
		return true;

}

int Entity::checkPlatformVectorCollision(std::vector<sf::Sprite*> platforms){
	for(int i = 0; i < platforms.size(); i++){
		if(checkPlatformCollision(*platforms[i])) return i;
	}
	return -1;
}

Entity::~Entity(){}


