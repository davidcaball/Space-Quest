#include "game.h"
#include <iostream>
#include "constants.h"

Game::Game(float width, float height, sf::Texture &masterTex){
	//set games master texture
	masterTexture = &masterTex;

	//initialze background
	setBackground();

	//initialize ground
	ground.setTexture(*masterTexture);
	ground.setTextureRect(sf::IntRect(1, 2554, 1600, 20));
	sf::FloatRect groundRect = ground.getLocalBounds();
	ground.setOrigin(groundRect.left, groundRect.top);
	ground.setScale(sf::Vector2f(1.0f, 2.0f));
	ground.setPosition(0, height - 40);

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
			if(e.joystickButton.button == 7) return -1;
		}
		if(e.type == sf::Event::JoystickMoved){
				
	
			}
	}

	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 0){
		player.move(player.getMoveSpeed() * delta, 0);
	}
	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 0){
		player.move(player.getMoveSpeed() * delta * -1, 0);
	}

	//render objects and draw window
	window.draw(background);
	window.draw(player.sprite);
	window.draw(ground);
	window.display();
	return 1;
}


