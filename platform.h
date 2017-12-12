#include <SFML/Graphics.hpp>

class Platform{

public:	
	//flips the sprite left or right
	Platform(sf::Texture &tex, float x, float y);
	Platform(){}
	~Platform();
	sf::Sprite sprite;

private:
	bool occupied;

};