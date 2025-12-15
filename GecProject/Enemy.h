#pragma once
#include "Character.h"
class Enemy : public Character
{
public:

	void initGraphics(Graphics* texGraphics) override;
	void move();


private:

	std::string setAnimationName(Movement state);
};

