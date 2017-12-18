#!/usr/bin/bash

g++ -std=c++11 -c source/main.cpp source/menu.cpp source/game.cpp source/hero.cpp source/entity.cpp source/snake.cpp source/platform.cpp source/fireball.cpp source/controls.cpp
g++ -std=c++11 main.o menu.o game.o hero.o entity.o snake.o platform.o fireball.o controls.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio