#include "../headers/hero.h"
#include "../headers/constants.h"
#include <iostream>
#include <math.h> 


// ************ Constructors ************

Hero::Hero(sf::Texture &tex){
	setTexture(tex);
	sprite = new sf::Sprite();
	jumps = Constants::NUM_JUMPS;
	airDodgeTimer = Constants::AIR_DODGE_TIME;
	hitTimer = Constants::HIT_ANIM_TIME;
	invincible = false;
	canAirDodge = false;
	hitPoints = 10;
	hit = false; //flag for seeing if hero has been hit
	setVelocity(0.0f,0.0f);
	setAcceleration(0,0);
	baseAcceleration = Constants::PLAYER_ACCELERATION;
}


// ************ Setters ************

void Hero::setVelocity(float x, float y){
	velocity.x = x;
	velocity.y = y;

	if(velocity.x > Constants::PLAYER_MAX_VELOCITY)
		velocity.x = Constants::PLAYER_MAX_VELOCITY;
	if(velocity.x < Constants::PLAYER_MAX_VELOCITY * -1)
		velocity.x = Constants::PLAYER_MAX_VELOCITY * -1;
	if(velocity.y > Constants::PLAYER_MAX_FALL_SPEED)
		velocity.y = Constants::PLAYER_MAX_FALL_SPEED;

}

void Hero::setAirDodge(bool toggle){
	canAirDodge = toggle;
}

void Hero::setOrientation(){
	float scale = Constants::SPRITE_SCALE;
	if(velocity.x > 0) sprite->setScale(scale, scale);
	else if(velocity.x < 0) sprite->setScale(-scale, scale);
}

void Hero::setJumpSprite(){
	sprite->setTextureRect(sf::IntRect(353, 62, 18, 23));
}


// ************ Getters ************

bool Hero::getAirDodge(){
	return canAirDodge;
}

bool Hero::isInvincible(){
	return invincible;
}

// ************ Movement ************

void Hero::jump(){
	if(jumps > 0){
		canAirDodge = true;
		velocity.y = Constants::JUMP_SPEED * -1;
		jumps--;
	}
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
		sprite->setTextureRect(sf::IntRect(578, 60, 17, 24));
	}
}





void Hero::update(float delta){

	setOrientation();
	setVelocity(velocity.x + acceleration.x * delta, velocity.y + acceleration.y * delta);
	sprite->setPosition(sprite->getPosition().x + velocity.x * delta, sprite->getPosition().y + velocity.y * delta);

	//check if player should be playing hit animation
	if(hit){
		hitTimer -= delta;
		if(hitTimer % 200 > 100)
			sprite->setColor(sf::Color::Red);
		else sprite->setColor(sf::Color::White);
		if(hitTimer <= 0){
			hitTimer = Constants::HIT_ANIM_TIME;
			hit = false;
			invincible = false;
		}
	}
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
			sprite->setTextureRect(sf::IntRect(1, 62, 18, 23));
		}
		return;
	}

	//friction
	float temp = getVelocity().x;
	if(getVelocity().x != 0){
		setVelocity(getVelocity().x - Constants::FRICTION * delta * ((getVelocity().x > 0) ? 1 : -1), 
							   	getVelocity().y);
		//comparison is used to test whether there was a switch in velocity from pos to neg
		//if there is just set velocity to 0 to revent jittering
		if(temp * getVelocity().x < 0) setVelocity(0, getVelocity().y);
	}

	//checks if sprite is below the ground level, corrects if it is.
	//if it is above ground gravity acts on it
	if(sprite->getPosition().y < Constants::WINDOW_HEIGHT - 40){
		setVelocity(velocity.x, velocity.y + Constants::GRAVITY * delta);
	}else{
			velocity.y = 0;
			sprite->setPosition(sf::Vector2f(sprite->getPosition().x, Constants::WINDOW_HEIGHT - 40));
			restoreJumps();
			restoreAirDodge();
			setAirDodge(false);
	}

}



bool Hero::checkPlatformCollision(sf::Sprite object){
	//checking bounds of both object to see if they intersect
	if(object.getPosition().y < sprite->getPosition().y 
		&& object.getPosition().y + object.getLocalBounds().height  + 20> sprite->getPosition().y
		&& object.getPosition().x < sprite->getPosition().x
		&& object.getPosition().x + object.getLocalBounds().width * Constants::PLATFORM_W_SCALE + sprite->getLocalBounds().width * 1 > sprite->getPosition().x){
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
	sprite->setTextureRect(sf::IntRect(1, 62, 18, 23));
	jumps = Constants::NUM_JUMPS;
}




void Hero::restoreAirDodge(){
	airDodgeTimer = Constants::AIR_DODGE_TIME;
	canAirDodge = true;
}

//checks collision between two entities
bool Hero::checkSnakeCollision(Snake object){
	sf::Vector2f spriteCenter(sprite->getPosition().x - sprite->getOrigin().x + sprite->getLocalBounds().width / 2,
		sprite->getPosition().y - sprite->getOrigin().y + sprite->getLocalBounds().height / 2);

	sf::Vector2f objectCenter(object.getSprite()->getPosition().x - object.getSprite()->getOrigin().x + object.getSprite()->getLocalBounds().width / 2,
		object.getSprite()->getPosition().y - object.getSprite()->getOrigin().y + object.getSprite()->getLocalBounds().height / 2);

	float distance = sqrt(pow((spriteCenter.x - objectCenter.x), 2) + pow((spriteCenter.y - objectCenter.y), 2));
	if(distance < Constants::SNAKE_COLLISION_BUFFER){
		return true;
	}
	return false;
}

//checks collision of a vector of entities, returns index of entity
//that is colliding
int Hero::checkSnakeVectorCollision(std::vector<Snake*> objectList){
	for(int i = 0; i < objectList.size(); i++){
		if(checkSnakeCollision(*objectList[i]))
			return i;
	}
	return -1;
}



void Hero::loseHP(){
	std::cout << "I've been hit" << std::endl;
	invincible = true;
	hitPoints--;
	hit = true;
}



Hero::~Hero(){}


