#include <SFML/Graphics.hpp>

class Platform{

public:	
	//flips the sprite left or right
	Platform(sf::Texture &tex, float xPos, float yPos);
	Platform(){}
	~Platform();
	bool isOccupied();
	sf::Sprite sprite;

private:
	bool occupied;

};