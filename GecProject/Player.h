#pragma once
#include "Character.h"
class Player : public Character
{
public: 

	void move();
	void initGraphics(Graphics* texGraphics) override; 

private:

	
	std::string setAnimationName(Movement state);
};

