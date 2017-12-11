#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"

//g++ -c main.cpp
//g++ main.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system

	
int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    Menu menu(window.getSize().x, window.getSize().y);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
      //  window.draw(shape);
        menu.draw(window);
        window.display();
    }

    return 0;
}