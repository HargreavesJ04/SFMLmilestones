#include "Collision.h"
#include <iostream>

Collision::Collision(sf::FloatRect boxcollider)
{
    collider = boxcollider;
}

void Collision::Move(sf::Vector2f newPosition)
{
    collider.position = newPosition;
}

bool Collision::CheckCollision(sf::FloatRect OtherActor)
{
   
    if (const std::optional intersection = collider.findIntersection(OtherActor))
    {
       // std::cout << "Collision Detected!" << std::endl;
        return true; 
    }

    return false;
}