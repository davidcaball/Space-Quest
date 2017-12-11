#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height){
	if(!font.loadFromFile("arial.ttf")){
		//error
	}
	play.setFont(font);
	play.setColor(sf::Color::Red);
	play.setString("Play");
	play.setPosition(sf::Vector2f(width / 2, height / 2));
}

Menu::~Menu(){

}

void Menu::draw(sf::RenderWindow &window){
	window.draw(background);
	window.draw(play);
}

void Menu::setBackground(sf::Texture  &backgroundTexture){
    sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    background = bg;
}