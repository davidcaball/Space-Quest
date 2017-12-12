#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen.h"
#include "menu.h"
#include "game.h"
#include <SFML/Audio.hpp>


//g++ -c main.cpp
//g++ main.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system

//Joystick
// A = 0
// B = 1
// X = 2
// Y = 3
// L = 4
// R = 5
// Sel = 6
// Start = 7
// X/Y = -100 || 100 || 0



Menu createMenu(sf::Window &window, sf::Texture &bg);	
Game createGame(sf::Window &window, sf::Texture &bg);   

int main()
{   
    sf::Event e;

    //create system clock for measuring time between rendered frames
    sf::Clock clock;
    sf::Time elapsed;

    //Create Render window
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Space Quest");

    //Create Menu
    //TODO create single texture file

    sf::Texture masterTexture;
    if(!masterTexture.loadFromFile("resources/spritesheet.png")){
        std::cerr << "Could not load masterTexture file" << std:: endl;
    }

    Menu menu = createMenu(window, masterTexture);
    Game game = createGame(window, masterTexture);

    //create a vector of screens to handle changing between them
    std::vector<Screen*> screens;
    int screen = 0;
    screens.push_back(&menu);
    screens.push_back(&game);

    //Render graphics
    while (screen >= 0)
    {   
        elapsed = clock.getElapsedTime();
        clock.restart();
        screen = screens[screen]->Run(window, elapsed.asMilliseconds());
    }

    return 0;
}
//takes a window and texture by reference, sets the background and returns menu
//back to main
Menu createMenu(sf::Window &window, sf::Texture &bg){

    Menu menu(window.getSize().x, window.getSize().y);
    menu.setBackground(bg);
    return menu;
}

Game createGame(sf::Window &window, sf::Texture &bg){

    Game game(window.getSize().x, window.getSize().y, bg);
    return game;
}