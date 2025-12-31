#include "Enemy.h"
#include "level.h"

void Enemy::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);
}

void Enemy::move(float dt, const level& map)
{
	currentState = Idle;
	box.Move(position);

	if (texGraphics)
	{
		std::string animName = setAnimationName(currentState);
		texGraphics->RenderSprite(spriteID, position, animName, 0);
	}
}

void Enemy::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		position = { -5000.f, -5000.f };
		box.Move(position);
	}
}

std::string Enemy::setAnimationName(Movement state)
{
	switch (state)
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