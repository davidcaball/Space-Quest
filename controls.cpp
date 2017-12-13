#include "controls.h"
#include <iostream>

ControlScreen::ControlScreen(float width, float height){
	
}

ControlScreen::ControlScreen(float width, float height, sf::Texture &masterTexture){
	background.setTexture(masterTexture);
	background.setTextureRect(sf::IntRect(0, 3794, 1600, 1200));
	background.setPosition(sf::Vector2f(0,0));
}

ControlScreen::~ControlScreen(){
}



int ControlScreen::Run(sf::RenderWindow &window, float delta){
	sf::Event e;

	while(window.pollEvent(e)){ //step through all events
			if(e.type == sf::Event::JoystickButtonPressed){
				if(e.joystickButton.button == 1){	
					return 0;
				}
			}
	}

	//render objects and draw window
	window.draw(background);
	window.display();
	return 2;
}

void ControlScreen::setBackground(sf::Texture  &backgroundTexture){
    sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    bg.setTextureRect(sf::IntRect(0, 125, 1600, 1200));
    background = bg;
}