#pragma once
#include "Game.h" 
#include "Character.h"

class Collision
{
public:
	
	Collision(sf::FloatRect& boxcollider); 

	bool CheckCollision(sf::FloatRect OtherActor);
private: 

	sf::FloatRect collider;
};

