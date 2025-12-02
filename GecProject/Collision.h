#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	
	Collision(sf::FloatRect boxcollider); 

	bool CheckCollision(sf::FloatRect OtherActor);

private: 

	sf::FloatRect collider;
};

