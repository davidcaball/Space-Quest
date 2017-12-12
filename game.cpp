#include "game.h"
#include <iostream>

Game::Game(float width, float height, sf::Texture &masterTex){
	masterTexture = &masterTex; 
	player = Hero(*masterTexture);


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
		
	}

	//render objects and draw window
	window.draw(background);
	window.display();
	return 1;
}


