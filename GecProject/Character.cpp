#include "Character.h"


void Character::initGraphics(Graphics* graphics)
{
	texGraphics = graphics;
}

void Character::takeDamage(int damage)
{

	health -= damage;
	if (health < 0) health = 0;
	std::cout << "Took Damage! HP: " << health << std::endl;
}

bool Character::CheckCollision(Character& other)
{
	sf::FloatRect otherRect = other.box.GetBox();
	return box.CheckCollision(otherRect);
}



