#include "Collision.h"

Collision::Collision(sf::FloatRect& boxcollider)
{
	collider = boxcollider;
}

bool Collision::CheckCollision(sf::FloatRect OtherActor)
{
	
	if (const std::optional intersection = collider.findIntersection(OtherActor))
	{
		std::cout << "Collision Detected!" << std::endl;
	}

	return false;
} 
