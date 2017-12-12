#include "entity.h"

class Hero : public Entity{

public:	
	void update(float delta);
	void attack();
	void setVelocity(sf::Vector2f velocityArg);
	void jump();
	bool checkPlatformCollision(sf::Sprite object);
	int checkPlatformVectorCollision(std::vector<Platform*>);
	void restoreJumps();
	void airDodge();
	void setJumpSprite();
	float getAirDodgeTimer();
	void restoreAirDodge();
	//flips the sprite left or right
	void setOrientation();
	Hero(sf::Texture &tex);
	Hero(){}
	~Hero();

private:
	bool canAirDodge;
	bool invincible;
	bool airDodging;
	float airDodgeTimer;
	int ammo;
	int jumps;

};
