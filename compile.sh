#!/usr/bin/bash

g++ -c main.cpp menu.cpp game.cpp hero.cpp entity.cpp snake.cpp platform.cpp
g++ main.o menu.o game.o hero.o entity.o snake.o platform.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./main-app