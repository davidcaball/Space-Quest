#include "entity.h"

class Snake : public Entity{

public:	
	void update(float delta);
	void animate(float delta);
	//flips the sprite left or right
	Snake(sf::Texture &tex);
	Snake(){}
	~Snake();

private:
	long animationClock;
	sf::Sprite * home;

};
