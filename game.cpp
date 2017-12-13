#include "game.h"
#include <iostream>
#include "constants.h"
#include <time.h>

Game::Game(float width, float height, sf::Texture &masterTex){
	srand(time(NULL));
	//initialize view
	view = sf::View(sf::FloatRect(0,0,width, height));
	backgroundChanged = false;

	//set games master texture
	masterTexture = &masterTex;
	windowHeight = height;
	windowWidth = width;

	//initialze background
	setBackground();

	//initialize ground
	ground.setTexture(*masterTexture);
	ground.setTextureRect(sf::IntRect(1, 2554, 1600, 20));
	sf::FloatRect groundRect = ground.getLocalBounds();
	ground.setOrigin(groundRect.left, groundRect.top);
	ground.setScale(sf::Vector2f(1.0f, 2.0f));
	ground.setPosition(0, height - 40);

	//create vector of platforms
	createPlatformVector();

	//initialize snakes
	createSnakeVector();

	//initialize fireballs
	fireballTimer = Constants::FIREBALL_RATE;


	//initialize players sprite 
	player = Hero(*masterTexture);
	player.sprite.setTexture(*masterTexture);
	player.sprite.setTextureRect(sf::IntRect(1, 62, 18, 23));
	player.sprite.setScale(sf::Vector2f(Constants::SPRITE_SCALE, Constants::SPRITE_SCALE));

	sf::FloatRect playerRect = player.sprite.getLocalBounds();
	player.sprite.setOrigin(playerRect.left + playerRect.width / 2, 
		playerRect.top + playerRect.height);
	player.sprite.setPosition(width / 2, -30000);
	player.setMoveSpeed(Constants::PLAYER_MOVE_SPEED);
	player.setVelocity(sf::Vector2f(0,0));
	player.setAcceleration(Constants::PLAYER_ACCELERATION);


}

void Game::setBackground(){
	sf::Sprite bg;
    bg.setTexture(*masterTexture);
    bg.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
    bg.setOrigin(bg.getLocalBounds().left + bg.getLocalBounds().width / 2, 
    	bg.getLocalBounds().top + bg.getLocalBounds().height / 2);
    background = bg;
}

int Game::Run(sf::RenderWindow &window, float delta){
	sf::Event e;

	while(window.pollEvent(e)){ //step through all events
		if(e.type == sf::Event::JoystickButtonPressed){
			if(e.joystickButton.button == 7) return 0;
			if(e.joystickButton.button == 2){
				std::cout << "Input: X" << std::endl;
 				player.jump();
			}	
			if(e.joystickButton.button == 4 && player.getAirDodge()){
				std::cout << "Input: L" << std::endl;
				player.airDodge();
			}	
			//TODO remove this
			if(e.joystickButton.button == 6){
				std::cout << player.sprite.getPosition().x << ","
				<< player.sprite.getPosition().y << ", " << std::endl;
			}	
		}
		if(e.type == sf::Event::JoystickMoved){
		
		}
	}

	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100){
		player.setVelocity(sf::Vector2f(player.getVelocity().x + player.getAcceleration() * delta, player.getVelocity().y));
	}
	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100){
		player.setVelocity(sf::Vector2f(player.getVelocity().x + player.getAcceleration() * delta * -1, player.getVelocity().y));
	}


	//logic to loop through a vector of platforms to see if any are colliding with player
	int collided = player.checkPlatformVectorCollision(platforms);
	if(collided >= 0 && player.getVelocity().y > 0){
		player.restoreJumps(); //jumps and air dodge ability restored upon landing
		player.restoreAirDodge();
		player.setAirDodge(false);
		player.setVelocity(sf::Vector2f(player.getVelocity().x, 0));
		player.sprite.setPosition(sf::Vector2f(player.sprite.getPosition().x, platforms[collided]->sprite.getPosition().y));
	}

	//logic to check for collision with snakes
	int snakeCollision = player.checkSnakeVectorCollision(snakes);
	if(snakeCollision >= 0 && !player.isInvincible()){
		player.loseHP();
	}

	//fireball logic
	fireballTimer -= delta;
	if(fireballTimer < 0){
		std::cout << "Trying to create fireball" << std::endl;
		int chance = 2;
		if(player.sprite.getPosition().y < -30000)
			chance = 10;
		else if(player.sprite.getPosition().y <-20000)
			chance = 7;
		else if(player.sprite.getPosition().y <-10000)
			chance = 5;
		else if(player.sprite.getPosition().y < -5000)
			chance = 2;
		int randN = rand() % 10;
		std::cout << randN << std::endl;
		if(randN < chance) createFireball();
		fireballTimer = Constants::FIREBALL_RATE;
	}
	//update view to follow player
	updateView();

	//update background to follow View and get darker
	updateBackground();

	//update player
	player.update(delta);

	//render objects and draw window
	window.setView(view);
	window.draw(background);
	window.draw(ground);

	//draw all platforms
	for(int i = 0; i < platforms.size(); i++)
		window.draw(platforms[i]->sprite);

	//draw all snakes
	for(int i = 0; i < snakes.size(); i++){
		snakes[i]->update(delta);
		window.draw(snakes[i]->sprite);
	}

	//render fireballs
	for(int i = 0; i < fireballs.size(); i++){
		fireballs[i]->update(delta);
		window.draw(fireballs[i]->sprite);
	}

	

	window.draw(player.sprite);
	window.display();
	return 1;
}



Platform * Game::createPlatform(int num){
	

	int xPos = rand() % static_cast<int>(windowWidth - Constants::PLATFORM_WIDTH);
	int yPos = windowHeight - ((rand() % 100)  + num * Constants::PLATFORM_SEPERATION);
	//std::cout << "Platform at " << xPos << ", " << yPos << std::endl;
	Platform * newPlatform = new Platform(*masterTexture, xPos, yPos);
	return newPlatform;

}

void Game::createPlatformVector(){
	srand(time(NULL));
	for(int i = 0; i < Constants::MAX_NUM_PLATFORMS; i++){
		platforms.push_back(createPlatform(i + 1));
	}
}


void Game::createSnakeVector(){
	 bool added = false;
	 int randNum;
	 for(int i = 0; i < Constants::NUM_SNAKES && i < platforms.size(); i++){
	 	added = false;
	 	while(!added){
	 		randNum = rand() % platforms.size();
	 		if(platforms[randNum]->isOccupied()){
	 			continue;
	 		}
	 		else{
	 			std::cout << "Creating Snake" << std::endl;
	 			Snake * newSnake = new Snake(*masterTexture, platforms[randNum]);
	 			snakes.push_back(newSnake);
	 			added = true;
	 		}
	 	}
	 }
}

void Game::createFireball(){
	float modifier = rand() % 250;
	Fireball * newFireball = new Fireball(*masterTexture, 1640, player.sprite.getPosition().y - 500 - modifier);
	fireballs.push_back(newFireball);
	std::cout << "Fireball Created" << std::endl;
}

void Game::updateView(){
	float yPos = player.sprite.getPosition().y;
	if(yPos > windowHeight / 2) yPos = windowHeight / 2;
	view.setCenter(sf::Vector2f(windowWidth / 2, yPos));
}

void Game::updateBackground(){
	
	float yPos = player.sprite.getPosition().y;

	//if player gets back to searth from space, change texture back to sky
	if(backgroundChanged && yPos > -38000){
		background.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
		backgroundChanged = false;
	}

	if(yPos > windowHeight / 2) yPos = windowHeight / 2;
	background.setPosition(sf::Vector2f(windowWidth / 2, yPos));
	float ratio = yPos / (windowHeight / 2) * 5;
	float red = 255 + ratio;
	float green = 255 + ratio;
	float blue = 255 + ratio * .8;
	//conditions stop color from looping over back to white
	if(red < 0) red = 0;
	if(green < 0) green = 0;
	if(blue < 0) blue = 0;
	if(yPos < 0) background.setColor(sf::Color(red, green, blue));

	//once player gets high enough, stars appear
	if(yPos < -38000 && !backgroundChanged){
		background.setTextureRect(sf::IntRect(0, 2590, 1600, 1200));
		background.setColor(sf::Color(0,0,0));
		backgroundChanged = true;
	}
	//stars gradually fade in
	if(yPos < -38000){
		ratio = (yPos + 38000) / (windowHeight / 2) * 10;
		red = 0 - ratio;
		green = 0 - ratio;
		blue = 0 - ratio;

		if(blue > 255) blue = 255;
		if(red > 255) red = 255;
		if(green > 255) green = 255;

		background.setColor(sf::Color(red, green, blue));
	}
}

Game::~Game(){

}



