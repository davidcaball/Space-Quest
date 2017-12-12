#include "entity.h"

class Hero : public Entity{

public:	
	void update(float delta);
	void attack();
	void setVelocity(sf::Vector2f velocityArg);
	void jump();
	bool checkPlatformCollision(sf::Sprite object);
	int checkPlatformVectorCollision(std::vector<sf::Sprite*>);
	void restoreJumps();
	void airDodge();
	float getAirDodgeTimer();
	Hero(sf::Texture &tex);
	Hero(){}
	~Hero();

private:
	bool invincible;
	bool airDodging;
	float airDodgeTimer;
	int ammo;
	int jumps;

};
