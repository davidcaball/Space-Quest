#include "entity.h"

class Hero : public Entity{

public:	

	void attack();
	Hero(sf::Texture &tex);
	Hero(){}
	~Hero();

private:
	int ammo;
};
