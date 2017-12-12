#include "entity.h"

class Hero : public Entity{

public:	

	void attack();
	void setVelocity(sf::Vector2f velocityArg);
	Hero(sf::Texture &tex);
	Hero(){}
	~Hero();

private:
	int ammo;

};
