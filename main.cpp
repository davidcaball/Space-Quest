#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "screen.h"
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
    sf::Texture menuBackgroundTexture;
    if(!menuBackgroundTexture.loadFromFile("resources/background.jpeg")){
        std::cerr << "Error Loading background image" << std::endl;
    }

    Menu menu = createMenu(window, menuBackgroundTexture);

    sf::Texture gameBackgroundTexture;
    if(!gameBackgroundTexture.loadFromFile("resources/sky.png")){
        std::cerr << "Error loading game background image" << std::endl;
    }

    Game game = createGame(window, gameBackgroundTexture);

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

    Game game(window.getSize().x, window.getSize().y);
    game.setBackground(bg);
    return game;
}