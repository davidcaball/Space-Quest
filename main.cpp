#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"

//g++ -c main.cpp
//g++ main.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system

Menu createMenu(sf::Window &window, sf::Texture &bg);	

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    //Create Menu
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("background.jpeg")){
        std::cerr << "Error Loading background image" << std::endl;
    }
    Menu menu = createMenu(window, backgroundTexture);
    

    while (window.isOpen())
    {
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

Menu createMenu(sf::Window &window, sf::Texture &bg){

    Menu menu(window.getSize().x, window.getSize().y);
    menu.setBackground(bg);
    return menu;
}