#pragma once
#include "Game.h" 
#include "Character.h"

class Collision
{
public:
	int colliderX;
	int colliderY;
	int colliderWidth;
	int colliderHeight;


	bool CheckCollision(Character& OtherActor);
private: 


};

