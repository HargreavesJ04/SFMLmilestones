#pragma once
#include "Character.h"

class level;

class Enemy : public Character
{
public:

	std::string spriteID;
	void initGraphics(Graphics* texGraphics) override;
	void move(float dt, const level& map);
	void takeDamage(int damage) override;

private:

	int direction = 1;
	std::string setAnimationName(Movement state);
};

