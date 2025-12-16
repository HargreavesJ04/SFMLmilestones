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
		std::string animName = setState(currentState);
		texGraphics->RenderSprite("Player", position, animName, 0);
	}
}




void Player::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);

	texGraphics->AddAnimationSet("IDLE", "Player", AnimationData{ "IDLEtex",5});
	texGraphics->AddAnimationSet("ATTACK", "Player", AnimationData{ "ATTACKtex", 8});
	texGraphics->AddAnimationSet("WALK", "Player", AnimationData{ "WALKtex", 5});
	texGraphics->AddAnimationSet("CROUCH", "Player", AnimationData{ "WALKtex", 5});
	texGraphics->AddAnimationSet("JUMP", "Player", AnimationData{ "WALKtex", 5});
}

void Player::initAudio(Audio* audio)
{
	Character::initAudio(audio);

	audio->LoadSound("ATTACK", "Data/Audio/sfx/Alucard/cutt.wav");
	audio->LoadSound("WALK", "Data/Audio/sfx/Alucard/alu_agh.wav");
	audio->LoadSound("HURT", "Data/Audio/sfx/Alucard/alu_agh.wav");


}

std::string Player::setState(Movement state)
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
