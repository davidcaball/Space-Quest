#!/usr/bin/bash

g++ -c main.cpp
g++ main.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system
./main-app