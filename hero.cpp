#include "hero.h"
#include "constants.h"
#include <iostream>

Hero::Hero(sf::Texture &tex){
	setTexture(tex);
	sf::Sprite sprite;
	jumps = Constants::NUM_JUMPS;
	airDodgeTimer = Constants::AIR_DODGE_TIME;
	canAirDodge = true;
}

void Hero::setVelocity(sf::Vector2f velocityArg){
	velocity = velocityArg;
	if(velocity.x > Constants::PLAYER_MAX_VELOCITY)
		velocity.x = Constants::PLAYER_MAX_VELOCITY;
	if(velocity.x < Constants::PLAYER_MAX_VELOCITY * -1)
		velocity.x = Constants::PLAYER_MAX_VELOCITY * -1;
	if(velocity.y > Constants::PLAYER_MAX_FALL_SPEED)
		velocity.y = Constants::PLAYER_MAX_FALL_SPEED;

}

void Hero::update(float delta){
	//setVelocity(sf::Vector2f(velocity.x, velocity.y));
	setOrientation();
	sprite.setPosition(sprite.getPosition().x + velocity.x * delta, sprite.getPosition().y + velocity.y * delta);

	//check if player is airdodging
	if(airDodging){
		airDodgeTimer-= delta;
		if(airDodgeTimer < 170){
			velocity.x = 0;
			velocity.y = 0;
		}
		if(airDodgeTimer <= 0){
			airDodging = false;
			invincible = false;
			sprite.setTextureRect(sf::IntRect(1, 62, 18, 23));
		}
		return;
	}

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
			restoreJumps();
			restoreAirDodge();
	}

}

void Hero::jump(){
	if(jumps > 0){
		velocity.y = Constants::JUMP_SPEED * -1;
		jumps--;
	}
}

bool Hero::checkPlatformCollision(sf::Sprite object){
	//checking bounds of both object to see if they intersect
	if(object.getPosition().y < sprite.getPosition().y 
		&& object.getPosition().y + object.getLocalBounds().height > sprite.getPosition().y
		&& object.getPosition().x < sprite.getPosition().x
		&& object.getPosition().x + object.getLocalBounds().width + sprite.getLocalBounds().width * 2 > sprite.getPosition().x){
		return true;
	}
}

int Hero::checkPlatformVectorCollision(std::vector<Platform*> platforms){
	//loop through vector and call helper method to check collision
	for(int i = 0; i < platforms.size(); i++){
		if(checkPlatformCollision(platforms[i]->sprite)) return i;
	}
	return -1;
}

void Hero::restoreJumps(){
	sprite.setTextureRect(sf::IntRect(1, 62, 18, 23));
	jumps = Constants::NUM_JUMPS;
}

//air dodging makes you invincible and moves you quickly in a direction
void Hero::airDodge(){
	if(canAirDodge){
		invincible = true;
		airDodging = true;
		canAirDodge = false;
		if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100){
			velocity.x = Constants::AIR_DODGE_SPEED;
		}
		if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100){
			velocity.x = -Constants::AIR_DODGE_SPEED;
		}
		if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100){
			velocity.y = Constants::AIR_DODGE_SPEED;
		}
		if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100){
			velocity.y = -Constants::AIR_DODGE_SPEED;
		}
		sprite.setTextureRect(sf::IntRect(578, 60, 17, 24));
	}
}

void Hero::setJumpSprite(){
	sprite.setTextureRect(sf::IntRect(353, 62, 18, 23));
}

void Hero::setOrientation(){
	float scale = Constants::SPRITE_SCALE;
	if(velocity.x > 0) sprite.setScale(scale, scale);
	else if(velocity.x < 0) sprite.setScale(-scale, scale);
}

void Hero::restoreAirDodge(){
	airDodgeTimer = Constants::AIR_DODGE_TIME;
	canAirDodge = true;
}

Hero::~Hero(){}


