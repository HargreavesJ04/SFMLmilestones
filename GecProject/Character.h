#pragma once
#include "Entity.h"
#include "Sprite2D.h"
#include "graphics.h"

class Character : public Entity
{
public: 

	enum Movement
	{
		Jump,
		Crouch,
		Left,
		Right
	};

	void up();
	void down();
	void left();
	void right();

	void move();
	 

	bool moving = false; 
	bool movingBack = false; 

	float x = 0.f;
	float y = 0.f;

	float xspeed = 5.f;
	float yspeed = 10.f;

private: 




};

