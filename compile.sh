#!/usr/bin/bash

g++ -c main.cpp menu.cpp game.cpp hero.cpp entity.cpp
g++ main.o menu.o game.o hero.o entity.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./main-app