#include "Enemy.h"
#include "level.h"

void Enemy::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);
}

void Enemy::move(float dt, const level& map)
{
	currentState = Left; // Default to a moving state

	float speed = 2.0f;
	position.x += direction * speed;

	sf::FloatRect nextStep = box.GetBox();
	nextStep.position.x += direction * speed;

	sf::FloatRect floorCheck = nextStep;
	floorCheck.position.y += 64.f; // Look one tile down

	bool hasFloor = false;
	bool hitWall = false;

	for (const auto& tile : map.getTiles())
	{
		sf::FloatRect tileBounds = tile.getGlobalBounds();

		if (floorCheck.findIntersection(tileBounds))
		{
			hasFloor = true;
		}

		if (nextStep.findIntersection(tileBounds))
		{
			hitWall = true;
		}
	}

	if (!hasFloor || hitWall)
	{
		direction *= -1;
	}

	box.Move(position);

	if (direction == -1)
	{
		if (texGraphics) texGraphics->SetSpriteFlip(spriteID, true);
	}
	else
	{
		if (texGraphics) texGraphics->SetSpriteFlip(spriteID, false);
	}

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
		sf::Vector2f centerPos = { position.x + (50.f / 2.f), position.y + (52.f / 2.f) };
		texGraphics->RenderSprite(spriteID, centerPos, animName, 0);
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