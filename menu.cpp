#include "menu.h"

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
	window.draw(play);
}