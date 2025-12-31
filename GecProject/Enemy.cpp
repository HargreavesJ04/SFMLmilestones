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

	if (damageFlashTimer > 0.0f)
	{
		damageFlashTimer -= dt;
		texGraphics->SetSpriteColour(spriteID, sf::Color::Red);
	}
	else
	{
		texGraphics->SetSpriteColour(spriteID, sf::Color::White);
	}

	if (texGraphics)
	{
		std::string animName = setAnimationName(currentState);
		texGraphics->RenderSprite(spriteID, position, animName, 0);
	}
}

void Enemy::takeDamage(int damage)
{
	if (damageFlashTimer <= 0.0f)
	{
		health -= damage;
		damageFlashTimer = 0.2f;

		if (health <= 0)
		{
			position = { -5000.f, -5000.f };
			box.Move(position);
		}
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