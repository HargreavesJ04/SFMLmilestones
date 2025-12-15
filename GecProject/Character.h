#pragma once
#include "Entity.h"
#include "graphics.h"
#include "Collision.h"


class Character : public Entity
{
public:

	enum Movement
	{
		Idle,
		Jump,
		Crouch,
		Left,
		Right,
		Falling,
		Attack
	};

	
	virtual void initGraphics(Graphics* graphics);

	void takeDamage(int damage);
	bool CheckCollision(Character& other);

	bool moving = false;
	bool movingBack = false;
	bool airborne;
	float xspeed = 5.f;
	float yspeed = 10.f;
	
protected:

	Collision box{{position,size} };
	Graphics* texGraphics = nullptr;
	Movement currentState = Idle;
	

	//these dont do anything yet :/
	int health = 100;
};

