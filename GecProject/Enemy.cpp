#include "Enemy.h"


void Enemy::initGraphics(Graphics* texGraphics)
{


	Character::initGraphics(texGraphics);
	position = { 150.f, 100.f };

	texGraphics->AddAnimationSet("IDLE", "Enemy", AnimationData{ "EIDLEtex", 5});
	texGraphics->AddAnimationSet("WALK", "Enemy", AnimationData{ "EWALKtex", 5});
}

void Enemy::move()
{
	currentState = Idle;

	box.Move(position);

	if (texGraphics)
	{
		std::string animName = setAnimationName(currentState);
		texGraphics->RenderSprite("Enemy", position, animName, 0);
	}
}

std::string Enemy::setAnimationName(Movement state)
{
	switch(state)
	{
	case Movement::Left:
	case Movement::Right:
		return "WALK";
	case Movement::Attack:
		return "ATTACK";
	default:
		return "IDLE";
	}
}
