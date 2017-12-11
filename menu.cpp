#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height){
	if(!font.loadFromFile("arial.ttf")){
		//error
	}

	//Set settings for play button
	play.setFont(font);
	play.setColor(sf::Color::Red);
	play.setString("Play");
	play.setPosition(sf::Vector2f(width / 2, height / 2));

	//set settings for controls button

}

Menu::~Menu(){

}

int Menu::Run(sf::RenderWindow &window){
	window.draw(background);
	window.draw(play);
	window.display();
	return 0;
}

void Menu::setBackground(sf::Texture  &backgroundTexture){
    sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    background = bg;
}