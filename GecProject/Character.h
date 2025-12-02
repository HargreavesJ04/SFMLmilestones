#pragma once
#include "Entity.h"
#include "Sprite2D.h"
#include "graphics.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collision.h"


class Character : public Entity
{
public:

	enum Movement
	{
		Jump,
		Crouch,
		Left,
		Right,
		Falling
	};

	void up();
	void down();
	void left();
	void right();

	void move();
	void initGraphics();


	Graphics* texGraphics = new Graphics;
	bool moving = false;



	bool movingBack = false;
	bool airborne;

	

	float xspeed = 5.f;
	float yspeed = 10.f;

	sf::Vector2f position{ 1, 1 };
	sf::Vector2f size{ 1000, 1000 };



	Collision box{ {position,size} };
};

