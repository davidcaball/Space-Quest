#include "game.h"
#include <iostream>

Game::Game(float width, float height){

}

Game::~Game(){

}

void Game::setBackground(sf::Texture &backgroundTexture){
	sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    background = bg;
}

int Game::Run(sf::RenderWindow &window, float delta){
	sf::Event e;

	while(window.pollEvent(e)){ //step through all events
		
	}

	//render objects and draw window
	window.draw(background);
	window.display();
	return 1;
}


