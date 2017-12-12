#include "menu.h"
#include <iostream>
#include<typeinfo> //TODO remove this

Menu::Menu(float width, float height){
	if(!font.loadFromFile("resources/sofachromerg.ttf")){
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

	//create vector of menu items
	selectedItem = 0;
	items.push_back(&play);
	items.push_back(&controls);

	//load music file
	music = new sf::Music();
	 if(!music->openFromFile("resources/VeridisQuoTitle.ogg")){
		std::cerr << "Error opening music file" << std::endl;
	 }else
	 music->loop(true);
	 music->play();
}

Menu::~Menu(){
}

void Menu::scanInput(sf::RenderWindow &window, float delta){
	sf::Event e;
	timer += delta;
	while(window.pollEvent(e)){
	 //timer to limit amount of inputs per second
			items[0]->setColor(sf::Color::White);
			items[1]->setColor(sf::Color::White);
			items[selectedItem]->setColor(sf::Color::Red);
			if(e.type == sf::Event::JoystickMoved){
				if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 0)
					selectedItem++;
				if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 0)
					selectedItem--;
				if(selectedItem < 0) selectedItem *= -1;
				selectedItem = selectedItem % 2;
				std::cout <<  selectedItem << std::endl;
			}
	}
}

int Menu::Run(sf::RenderWindow &window, float delta){
	scanInput(window, delta);
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