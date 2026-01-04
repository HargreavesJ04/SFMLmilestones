#include "Enemy.h"
#include "level.h"

void Enemy::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);
}

void Enemy::move(float dt, const level& map)
{
	currentState = (direction == 1) ? Right : Left;

	float speed = 2.0f;
	position.x += direction * speed;

	box.Move(position);
	for (const auto& tile : map.getTiles())
	{
		auto intersect = box.GetIntersection(tile.getGlobalBounds());
		if (intersect.has_value())
		{
			if (intersect->size.x < intersect->size.y)
			{
				if (position.x < tile.getPosition().x)
				{
					position.x -= intersect->size.x;
				}
				else
				{
					position.x += intersect->size.x;
				}
				box.Move(position);
			}
		}
	}

	position.y += yspeed * 1.0f;
	box.Move(position);

	for (const auto& tile : map.getTiles())
	{
		auto intersect = box.GetIntersection(tile.getGlobalBounds());
		if (intersect.has_value())
		{
			if (intersect->size.y <= intersect->size.x)
			{
				if (position.y < tile.getPosition().y)
				{
					position.y -= intersect->size.y;
				}
				else
				{
					position.y += intersect->size.y;
				}
				box.Move(position);
			}
		}
	}

	sf::FloatRect bounds = box.GetBox();
	sf::FloatRect wallCheck = bounds;
	wallCheck.position.x += (direction * speed);

	sf::FloatRect floorCheck = bounds;
	floorCheck.position.x += (direction * (bounds.size.x / 2.f));
	floorCheck.position.y += bounds.size.y + 10.f;

	bool hasFloor = false;
	bool hitWall = false;

	for (const auto& tile : map.getTiles())
	{
		sf::FloatRect tileBounds = tile.getGlobalBounds();
		if (floorCheck.findIntersection(tileBounds)) hasFloor = true;
		if (wallCheck.findIntersection(tileBounds)) hitWall = true;
	}

	if (!hasFloor || hitWall)
	{
		direction *= -1;
	}

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