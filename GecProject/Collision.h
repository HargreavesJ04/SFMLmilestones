#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:

    Collision(sf::FloatRect boxcollider);
    void Move(sf::Vector2f newPosition);
    bool CheckCollision(sf::FloatRect OtherActor);

    std::optional<sf::FloatRect> GetIntersection(sf::FloatRect OtherActor);
    sf::FloatRect GetBox() { return collider; }
private:
    sf::FloatRect collider;
};