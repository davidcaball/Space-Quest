# Space-Quest
A simple game written in C++ using the SFML graphics library for CSCI-2380 final project. 
The intent is to utilize the graph data structure as well as other data structures learned this semester.

Help the elf get to space, watch out for snakes and fireballs!

Interesting Stuff:

Random Generation: All entities and platforms in the games are randomly generated, allowing for a different level every time it is played.

Graph utilization: Since platforms are randomly generated there has to be a sure path to a top. The platform positions are loaded onto a graph and a path finding alorithm is used to ensure there is a viable path to the top. If not it will recreate the level.

Inheritance: All moving objects (Player, Snakes, Fireballs) are subclasses of the Entity class. They inherit useful methods that apply to all moving objects.

Polymorphism: To handle changing between different screens a Screen class was created. The different screens (Game, Menu, Controls) are all subclasses of the Screen class. A vector of Screens is created to easily handle switching between them, and all the subclasses methods are called when needed.