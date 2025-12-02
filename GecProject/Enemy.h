#pragma once
#include "Character.h"
class Enemy : public Character
{
public:

	void initEnemyGraphics();

	Graphics* texGraphics = new Graphics;

 

	sf::Vector2f position{ 1, 1 };
	sf::Vector2f size{ 1000, 1000 };



	Collision box{ {position,size} };

};

