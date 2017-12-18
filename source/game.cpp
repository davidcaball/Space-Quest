#include "../headers/game.h"
#include "../headers/constants.h"
#include <iostream>
#include <time.h>
#include <cmath>
#include <string> 

Game::Game(float width, float height, sf::Texture &masterTex){
	srand(time(NULL));
	timer = 0;
	//initialize view
	view = sf::View(sf::FloatRect(0,0,width, height));
	backgroundChanged = false;

	//set fps counter
	font.loadFromFile("resources/arial.ttf");
	score.setFont(font);
	score.setString("0");
	score.setColor(sf::Color::Yellow);
	score.setCharacterSize(100);


	//set games master texture
	masterTexture = &masterTex;
	windowHeight = height;
	windowWidth = width;

	//initialze background
	setBackground();


	//initialize ground
	ground.setTexture(*masterTexture);
	ground.setTextureRect(sf::IntRect(1, 2554, 1600, 20));
	sf::FloatRect groundRect = ground.getLocalBounds();
	ground.setOrigin(groundRect.left, groundRect.top);
	ground.setScale(sf::Vector2f(1.0f, 2.0f));
	ground.setPosition(0, height - 40);

	//create vector of platforms
	createPlatformVector();
	assignNeighbors();
	verifyPlatforms();

	//initialize snakes
	createSnakeVector();

	//initialize fireballs
	fireballTimer = Constants::FIREBALL_RATE;


	//initialize players sprite 
	player = Hero(*masterTexture);
	player.getSprite()->setTexture(*masterTexture);
	player.getSprite()->setTextureRect(sf::IntRect(1, 62, 18, 23));
	player.getSprite()->setScale(sf::Vector2f(Constants::SPRITE_SCALE, Constants::SPRITE_SCALE));

	sf::FloatRect playerRect = player.getSprite()->getLocalBounds();
	player.getSprite()->setOrigin(playerRect.left + playerRect.width / 2, 
		playerRect.top + playerRect.height);
	player.getSprite()->setPosition(width / 2, ground.getPosition().y);
	player.setMoveSpeed(Constants::PLAYER_MOVE_SPEED);
	//max jump = 896
	//max distance = 685;

}

void Game::setBackground(){
	sf::Sprite bg;
    bg.setTexture(*masterTexture);
    bg.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
    bg.setOrigin(bg.getLocalBounds().left + bg.getLocalBounds().width / 2, 
    	bg.getLocalBounds().top + bg.getLocalBounds().height / 2);
    background = bg;
}

int Game::Run(sf::RenderWindow &window, float delta){
	fps++;
	timer+= delta;
	if(timer > 1000){
		score.setString(std::to_string(static_cast<int>(fps)));
		fps = 0;
		timer = 0;
	}

	score.setPosition(view.getCenter().x - 750, view.getCenter().y - 600);
	
	std::cout << "Delta: " << delta << std::endl;
	sf::Event e;
	
	if(player.hitPoints <= 0){
		player.getSprite()->setPosition(windowWidth / 2, ground.getPosition().y);
		player.hitPoints = 10;
		background.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
		background.setColor(sf::Color::White);

	}
	if(player.getSprite()->getPosition().x > maxHeight){
		maxHeight = player.getSprite()->getPosition().x;
	}

	while(window.pollEvent(e)){ //step through all events

		if(e.type == sf::Event::JoystickButtonPressed || e.type == sf::Event::KeyPressed){
			if(e.joystickButton.button == 7) return 0;
			if(e.joystickButton.button == 2 || e.key.code == sf::Keyboard::Up){
 				player.jump();
			}	
			if((e.joystickButton.button == 4 || e.key.code == sf::Keyboard::Space) && player.getAirDodge()){
				player.airDodge();
			}	
		}
	}

	//set players acceleration left or right if player is holding left or right
	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		player.accelerate(delta, 1);
	}
	if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		player.accelerate(delta, -1);
	}


	//logic to loop through a vector of platforms to see if any are colliding with player
	int collided = player.checkPlatformVectorCollision(platforms);
	if(collided >= 0 && player.getVelocity().y > 0){
		player.restoreJumps(); //jumps and air dodge ability restored upon landing
		player.restoreAirDodge();
		player.setAirDodge(false);
		player.setVelocity(player.getVelocity().x, 0);
		player.getSprite()->setPosition(sf::Vector2f(player.getSprite()->getPosition().x, platforms[collided]->sprite.getPosition().y));
	}

	//logic to check for collision with snakes
	int snakeCollision = player.checkEntityVectorCollision(snakes, Constants::SNAKE_COLLISION_BUFFER);
	if(snakeCollision >= 0 && !player.isInvincible()){
		player.loseHP();
	}

	//logic to check fireball collision
	//logic to check for collision with snakes
	int fireCollision = player.checkEntityVectorCollision(fireballs, Constants::FIREBALL_COLLISION_BUFFER);
	if(fireCollision >= 0 && !player.isInvincible()){
		player.loseHP();
	}

	//fireball logic
	fireballTimer -= delta;
	if(fireballTimer < 0){
		int chance = 2;
		if(player.getSprite()->getPosition().y < -30000)
			chance = 10;
		else if(player.getSprite()->getPosition().y <-20000)
			chance = 7;
		else if(player.getSprite()->getPosition().y <-10000)
			chance = 5;
		else if(player.getSprite()->getPosition().y < -5000)
			chance = 2;
		int randN = rand() % 10;
		if(randN < chance) createFireball();
		fireballTimer = Constants::FIREBALL_RATE;
	}
	//update view to follow player
	updateView();

	//update background to follow View and get darker
	updateBackground();

	//update player
	player.update(delta);

	//render objects and draw window
	window.setView(view);
	window.draw(background);
	window.draw(ground);

	//draw all platforms
	for(int i = 0; i < platforms.size(); i++)
		window.draw(platforms[i]->sprite);

	//draw all snakes
	for(int i = 0; i < snakes.size(); i++){
		snakes[i]->update(delta);
		window.draw(*(snakes[i]->getSprite()));
	}

	//render fireballs
	for(int i = 0; i < fireballs.size(); i++){
		fireballs[i]->update(delta);
		window.draw(*(fireballs[i]->getSprite()));
	}

	

	window.draw(*player.getSprite());
	window.draw(score);
	window.display();
	return 1;
}



Platform * Game::createPlatform(int num){
	

	int xPos = rand() % static_cast<int>(windowWidth - Constants::PLATFORM_WIDTH);
	int yPos = windowHeight - ((rand() % 100)  + num * Constants::PLATFORM_SEPERATION);
	Platform * newPlatform = new Platform(*masterTexture, xPos, yPos);

	return newPlatform;

}

void Game::createPlatformVector(){
	srand(time(NULL));
	for(int i = 0; i < Constants::MAX_NUM_PLATFORMS; i++){
		Platform * newPlatform = createPlatform(i + 1);
		platforms.push_back(newPlatform);
		platformGraph.addVertex(i);
	}
}

void Game::assignNeighbors(){
	for(int i = 0; i < platforms.size() - 2; i++){
		sf::Vector2f plat1Pos(platforms[i]->sprite.getPosition().x, platforms[i]->sprite.getPosition().y);
		sf::Vector2f plat2Pos(platforms[i + 1]->sprite.getPosition().x, platforms[i + 1]->sprite.getPosition().y);
		sf::Vector2f plat3Pos(platforms[i + 2]->sprite.getPosition().x, platforms[i + 2]->sprite.getPosition().y);
		
		if(sqrt(pow((plat1Pos.x - plat2Pos.x),2) + pow((plat1Pos.y - plat2Pos.y),2)) < 1200)
			platformGraph.addDirectedEdge(i, i + 1);
		if(sqrt(pow((plat1Pos.x - plat3Pos.x),2) + pow((plat1Pos.y - plat3Pos.y),2)) < 1200)
			platformGraph.addDirectedEdge(i, i + 2);
	}
}

void Game::verifyPlatforms(){
	platformGraph.display();
	if(!platformGraph.findPath(0, Constants::MAX_NUM_PLATFORMS - 1)){
		platforms.clear();
		platformGraph.clear();
		createPlatformVector();
		assignNeighbors();
		verifyPlatforms();
	}

}


void Game::createSnakeVector(){
	 bool added = false;
	 int randNum;
	 for(int i = 0; i < Constants::NUM_SNAKES && i < platforms.size(); i++){
	 	added = false;
	 	while(!added){
	 		randNum = rand() % platforms.size();
	 		if(platforms[randNum]->isOccupied()){
	 			continue;
	 		}
	 		else{
	 			Snake * newSnake = new Snake(*masterTexture, platforms[randNum]);
	 			snakes.push_back(newSnake);
	 			added = true;
	 		}
	 	}
	 }
}

void Game::createFireball(){
	float modifier = rand() % 250;
	Fireball * newFireball = new Fireball(*masterTexture, 1640, player.getSprite()->getPosition().y - 500 - modifier);
	fireballs.push_back(newFireball);
}

void Game::updateView(){
	float yPos = player.getSprite()->getPosition().y;
	if(yPos > windowHeight / 2) yPos = windowHeight / 2;
	view.setCenter(sf::Vector2f(windowWidth / 2, yPos));
}

void Game::updateBackground(){
	
	float yPos = player.getSprite()->getPosition().y;

	//if player gets back to searth from space, change texture back to sky
	if(backgroundChanged && yPos > -38000){
		background.setTextureRect(sf::IntRect(0, 1335, 1600, 1200));
		backgroundChanged = false;
	}

	if(yPos > windowHeight / 2) yPos = windowHeight / 2;
	background.setPosition(sf::Vector2f(windowWidth / 2, yPos));
	float ratio = yPos / (windowHeight / 2) * 5;
	float red = 255 + ratio;
	float green = 255 + ratio;
	float blue = 255 + ratio * .8;
	//conditions stop color from looping over back to white
	if(red < 0) red = 0;
	if(green < 0) green = 0;
	if(blue < 0) blue = 0;
	if(yPos < 0) background.setColor(sf::Color(red, green, blue));

	//once player gets high enough, stars appear
	if(yPos < -38000 && !backgroundChanged){
		background.setTextureRect(sf::IntRect(0, 2590, 1600, 1200));
		background.setColor(sf::Color(0,0,0));
		backgroundChanged = true;
	}
	//stars gradually fade in
	if(yPos < -38000){
		ratio = (yPos + 38000) / (windowHeight / 2) * 10;
		red = 0 - ratio;
		green = 0 - ratio;
		blue = 0 - ratio;

		if(blue > 255) blue = 255;
		if(red > 255) red = 255;
		if(green > 255) green = 255;

		background.setColor(sf::Color(red, green, blue));
	}
}

Game::~Game(){

}



