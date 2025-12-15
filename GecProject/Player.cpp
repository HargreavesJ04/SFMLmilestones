#include "Player.h"

void Player::move()
{
	if (health <= 0)
	{
		position = { -10000.f, -10000.f };
		box.Move(position);
		return;
	}

	currentState = Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		position.y -= yspeed;
		currentState = Jump;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		position.y += yspeed;
		currentState = Crouch;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		position.x -= xspeed;
		currentState = Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		position.x += xspeed;
		currentState = Right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
	{
		currentState = Attack;
	}

	box.Move(position);

	if (texGraphics) 
	{
		std::string animName = setAnimationName(currentState);
		texGraphics->RenderSprite("Player", position, animName, 0);
	}
}




void Player::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);

	texGraphics->AddAnimationSet("IDLE", "Player", AnimationData{ "IDLEtex",  5, 60, 62 });
	texGraphics->AddAnimationSet("ATTACK", "Player", AnimationData{ "ATTACKtex", 8,  432, 521 });
	texGraphics->AddAnimationSet("WALK", "Player", AnimationData{ "WALKtex", 5,  60, 62 });
	texGraphics->AddAnimationSet("CROUCH", "Player", AnimationData{ "WALKtex", 5,  60, 62 });
	texGraphics->AddAnimationSet("JUMP", "Player", AnimationData{ "WALKtex", 5,  60, 62 });
}

std::string Player::setAnimationName(Movement state)
{
	switch (state)
	{
	case Movement::Left:
	case Movement::Right:
		return "WALK"; 
	case Movement::Jump:
		return "JUMP";
	case Movement::Attack:
		return "ATTACK";
	case Movement::Crouch:
		return "CROUCH"; 
	default:
		return "IDLE";
	}
}
