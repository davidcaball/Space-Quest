#include "entity.h"
#include "constants.h"

class Snake : public Entity{

public:	
	void update(float delta);
	void animate(float delta);
	//flips the sprite left or right
	Snake(sf::Texture &tex, Platform * platform);
	Snake(){}
	~Snake();
	sf::Sprite sprite;

private:
	float scale;
	long animationClock;
	sf::Sprite * home;

};
