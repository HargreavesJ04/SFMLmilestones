#include "Character.h"




void Character::up()
{

}

void Character::down()
{

}

void Character::left()
{

}

void Character::right()
{

}

void Character::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		y -= yspeed;
		moving = true;
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		y += yspeed;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		x -= xspeed;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		x += xspeed;
		moving = true;
	}
   	
	

}
