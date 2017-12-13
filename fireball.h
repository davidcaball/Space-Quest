#include "entity.h"

class Fireball : public Entity{

public:
	Fireball(sf::Texture &tex);
	Fireball(sf::Texture &tex, float xPos,float yPos);
	Fireball();
	~Fireball();
	void update(float delta);
	void animate(float delta);
	void destroy();
private:
	int animationTimer;
};