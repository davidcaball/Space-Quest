#!/usr/bin/bash

g++ -c main.cpp menu.cpp
g++ main.o menu.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio