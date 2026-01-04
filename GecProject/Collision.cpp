#include "Collision.h"
#include <iostream>

Collision::Collision(sf::FloatRect boxcollider)
{
    collider = boxcollider;
}

void Collision::Move(sf::Vector2f newPosition)
{
	collider.position = newPosition; // Update the position of the collider 
}

bool Collision::CheckCollision(sf::FloatRect OtherActor) // Check for collision with another actor
{
   
    if (const std::optional intersection = collider.findIntersection(OtherActor))
    {
       // std::cout << "Collision Detected!" << std::endl;
        return true; 
    }

    return false;
}

std::optional<sf::FloatRect> Collision::GetIntersection(sf::FloatRect OtherActor)
{
	return collider.findIntersection(OtherActor); // Return the intersection rectangle if there is a collision
}