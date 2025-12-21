#include "Player.h"

void Player::move()
{
	if (health <= 0)
	{
		position = { -10000.f, -10000.f };
		box.Move(position);
		currentState = Dead;
		return;
	}
	Movement previousState = currentState;
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

	if (currentState != previousState)
	{
		
		stopSound(setState(previousState));
		std::string key = setState(currentState);

		if (key == "WALK")
		{
			playSoundLooped(key);
		}
		else
		{
			playSound(key);
		}
	}

	if (texGraphics) 
	{
		std::string animName = setState(currentState);
		texGraphics->RenderSprite("Player", position, animName, 0);
	}
}

void Player::update(float dt, const int* levelData)
{
	if (Iframes > 0.0f)
	{
		Iframes -= dt;

		int flicker = static_cast<int>(Iframes * 10);
		if (flicker % 2 == 0)
		{
			texGraphics->SetSpriteColour("Player", sf::Color(255, 0, 0, 200));
		}
		else
		{
			texGraphics->SetSpriteColour("Player", sf::Color(255, 255, 255, 50));
		}
	}
	else
	{
		texGraphics->SetSpriteColour("Player", sf::Color::White);
	}

	if (health <= 0)
	{
		position = { -10000.f, -10000.f };
		box.Move(position);
		currentState = Dead;
		return;
	}

	move();
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
	audio->LoadSound("HURT", "Data/Audio/sfx/Alucard/alu_aah.wav");


}

void Player::takeDamage(int damage)
{
	if (Iframes <= 0.0f)
	{
		health -= damage;
		Iframes = 1.0f; 

		playSound("HURT");

		std::cout << "Hit Health: " << health << std::endl;
	}
}

bool Player::checkLevelCollision(const int* tiles, unsigned int width, unsigned int height, sf::Vector2u tileSize)
{
	int leftTile = (int)(position.x / tileSize.x);
	int rightTile = (int)((position.x + size.x) / tileSize.x);
	int topTile = (int)(position.y / tileSize.y);
	int bottomTile = (int)((position.y + size.y) / tileSize.y);

	if (leftTile < 0) leftTile = 0;
	if (rightTile >= (int)width) rightTile = width - 1;
	if (topTile < 0) topTile = 0;
	if (bottomTile >= (int)height) bottomTile = height - 1;

	for (int i = leftTile; i <= rightTile; ++i)
	{
		for (int j = topTile; j <= bottomTile; ++j)
		{
			if (tiles[i + j * width] > 0)
			{
				return true;
			}
		}
	}
	return false;
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
