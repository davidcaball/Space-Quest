#include "game.h"
#include <iostream>
#include "constants.h"
#include <time.h>

Game::Game(float width, float height, sf::Texture &masterTex){

	//initialize view
	view = sf::View(sf::FloatRect(0,0,width, height));

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

	//initialize platform
	platform.setTexture(*masterTexture);
	platform.setTextureRect(sf::IntRect(1, 2554, Constants::PLATFORM_WIDTH, 20));
	sf::FloatRect platformRect = platform.getLocalBounds();
	platform.setOrigin(platformRect.left, platformRect.top);
	platform.setScale(sf::Vector2f(1.0f, 2.0f));
	platform.setPosition(width / 2, height - 300);

	//create vector of platforms
	createPlatformVector();

	//initialize players sprite 
	player = Hero(*masterTexture);
	player.sprite.setTexture(*masterTexture);
	player.sprite.setTextureRect(sf::IntRect(1, 62, 18, 23));
	player.sprite.setScale(sf::Vector2f(3.0f, 3.0f));

	sf::FloatRect playerRect = player.sprite.getLocalBounds();
	player.sprite.setOrigin(playerRect.left + playerRect.width, 
		playerRect.top + playerRect.height);
	player.sprite.setPosition(width / 2, ground.getPosition().y);
	player.setMoveSpeed(Constants::PLAYER_MOVE_SPEED);
	player.setVelocity(sf::Vector2f(0,0));
	player.setAcceleration(Constants::PLAYER_ACCELERATION);

}


Game::~Game(){

}


void Game::setBackground(){
	sf::Sprite bg;
    bg.setTexture(*masterTexture);
    bg.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
    background = bg;
}

int Game::Run(sf::RenderWindow &window, float delta){
	sf::Event e;

	while(window.pollEvent(e)){ //step through all events
		if(e.type == sf::Event::JoystickButtonPressed){
			if(e.joystickButton.button == 7) return 0;
			if(e.joystickButton.button == 2){
				player.jump();
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

	//logic to allow player to jump up through platform, but not down
	if(player.checkPlatformCollision(platform) && player.getVelocity().y > 0){
		player.setVelocity(sf::Vector2f(player.getVelocity().x, 0));
	}

	//logic to loop through a vector of platforms to see if any are colliding with player
	int collided = player.checkPlatformVectorCollision(platforms);
	if(collided >= 0 && player.getVelocity().y > 0){
		player.setVelocity(sf::Vector2f(player.getVelocity().x, 0));
	}
	
	//update view to follow player
	updateView();

	player.update(delta);

	//render objects and draw window
	window.setView(view);
	window.draw(background);
	window.draw(ground);
	window.draw(platform);

	for(int i = 0; i < platforms.size(); i++) 
		window.draw(*platforms[i]);

	window.draw(player.sprite);
	window.display();
	return 1;
}

void Game::createPlatformVector(){
	srand(time(NULL));
	for(int i = 0; i < Constants::MAX_NUM_PLATFORMS; i++){
		platforms.push_back(createPlatform(i + 1));
	}
}

sf::Sprite * Game::createPlatform(int num){
	

	float xPos = rand() % static_cast<int>(windowWidth - Constants::PLATFORM_WIDTH);
	float yPos = (rand() % 100)  + num * Constants::PLATFORM_SEPERATION;
	std::cout << "Platform at " << xPos << ", " << yPos << std::endl;
	sf::Sprite * newPlatform = new sf::Sprite();
	newPlatform->setTexture(*masterTexture);
	newPlatform->setTextureRect(sf::IntRect(1, 2554, Constants::PLATFORM_WIDTH, 20));
	sf::FloatRect newPlatformRect = newPlatform->getLocalBounds();
	newPlatform->setOrigin(newPlatformRect.left, newPlatformRect.top);
	newPlatform->setScale(sf::Vector2f(1.0f, 2.0f));
	newPlatform->setPosition(xPos, yPos);
	return newPlatform;

}

void Game::updateView(){
	float yPos = player.sprite.getPosition().y;
	if(yPos > windowHeight / 2) yPos = windowHeight / 2;
	view.setCenter(sf::Vector2f(windowWidth / 2, yPos));
}

