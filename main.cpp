#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"

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



Menu createMenu(sf::Window &window, sf::Texture &bg);	

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Quest");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    //Create Menu
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("background.jpeg")){
        std::cerr << "Error Loading background image" << std::endl;
    }
    Menu menu = createMenu(window, backgroundTexture);
    std::cout << sf::Joystick::getButtonCount(0);
    //Render graphics
    while (window.isOpen())
    {
    std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        menu.draw(window);
        window.display();
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