#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height){
	if(!font.loadFromFile("sofachromerg.ttf")){
		//error
	}

	//Set settings for play button
	play.setColor(sf::Color::White);
	play.setScale(sf::Vector2f(1.5f, 1.5f));
	play.setString("Play");
	play.setFont(font);
	sf::FloatRect  playRect = play.getLocalBounds();
	play.setOrigin(playRect.left + playRect.width/2.0f,
		playRect.top + playRect.height / 2.0f);
	play.setPosition(sf::Vector2f(width / 2.0, height / 2.0));


	//set settings for controls button
	controls.setFont(font);
	controls.setScale(sf::Vector2f(1.5f, 1.5f));
	controls.setColor(sf::Color::White);
	controls.setString("Controls");
	sf::FloatRect  controlsRect = controls.getLocalBounds();
	controls.setOrigin(controlsRect.left + controlsRect.width/2.0f,
		controlsRect.top + controlsRect.height / 2.0f);
	controls.setPosition(sf::Vector2f(width / 2.0, height / 2.0 + 100));
	
	//set settings for title
	title.setFont(font);
	title.setScale(sf::Vector2f(2.5f, 2.5f));
	title.setColor(sf::Color::White);
	title.setString("Space Quest");
	sf::FloatRect  titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width/2.0f,
		titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(width / 2.0, height / 2.0 - 400));
}

Menu::~Menu(){

}

int Menu::Run(sf::RenderWindow &window){
	window.draw(background);
	window.draw(play);
	window.draw(controls);
	window.draw(title);
	window.display();
	return 0;
}

void Menu::setBackground(sf::Texture  &backgroundTexture){
    sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    background = bg;
}