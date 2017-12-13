#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height){
	if(!font.loadFromFile("resources/sofachromerg.ttf")){
		//error
	}

	//initialize view
	view = sf::View(sf::FloatRect(0,0,width, height));
	//Set settings for play button
	play.setColor(sf::Color::Red);
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

	//set settings for exit button
	//Set settings for play button
	exit.setColor(sf::Color::White);
	exit.setScale(sf::Vector2f(1.5f, 1.5f));
	exit.setString("Exit");
	exit.setFont(font);
	sf::FloatRect  exitRect = exit.getLocalBounds();
	exit.setOrigin(exitRect.left + exitRect.width/2.0f,
		exitRect.top + exitRect.height / 2.0f);
	exit.setPosition(sf::Vector2f(width / 2.0, height / 2.0 + 200));

	
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
	items.push_back(&exit);

	//load music file
	music = new sf::Music();
	 if(!music->openFromFile("resources/VeridisQuoTitle.ogg")){
		std::cerr << "Error opening music file" << std::endl;
	 }else
	 music->setLoop(true);
	 music->setVolume(50);
	 music->play();

	 //load sounds
	 if(!buffer.loadFromFile("resources/buttonboop.ogg"))
	 	std::cerr << "Error opening sound file buttonboop" << std::endl;
	 sound.setBuffer(buffer);
}

Menu::~Menu(){
}



int Menu::Run(sf::RenderWindow &window, float delta){
	sf::Event e;

	while(window.pollEvent(e)){ //step through all events
			items[0]->setColor(sf::Color::White);
			items[1]->setColor(sf::Color::White);
			items[2]->setColor(sf::Color::White);
			items[selectedItem]->setColor(sf::Color::Red);
			if(e.type == sf::Event::JoystickMoved){
				if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 0){
					selectedItem++;
					sound.play();
				}
				if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 0){
					selectedItem--;
					sound.play();
				}
				if(selectedItem < 0) selectedItem = 2;
				selectedItem = selectedItem % 3;
				std::cout << selectedItem << std::endl;
			}
			if(e.type == sf::Event::JoystickButtonPressed){
				if(e.joystickButton.button == 0){	
					if(selectedItem == 0){
						//music->stop();
						return 1;
					}
					if(selectedItem == 1) return 2;
					if(selectedItem == 2) return -3; 
				}
			}
	}

	//render objects and draw window
	window.setView(view);
	window.draw(background);
	window.draw(play);
	window.draw(controls);
	window.draw(title);
	window.draw(exit);
	window.display();
	return 0;
}

void Menu::setBackground(sf::Texture  &backgroundTexture){
    sf::Sprite bg;
    bg.setTexture(backgroundTexture);
    bg.setTextureRect(sf::IntRect(0, 125, 1600, 1200));
    background = bg;
}