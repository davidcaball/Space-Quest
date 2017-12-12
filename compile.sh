#!/usr/bin/bash

g++ -c main.cpp menu.cpp game.cpp
g++ main.o menu.o game.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio