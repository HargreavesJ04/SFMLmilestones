#include "Character.h"


void Character::initGraphics()
{


	if (!texGraphics->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "IDLEtex"))
		std::cerr << "Failed to load texture: Idle (1).png\n";

	if (!texGraphics->loadTexture("Data/Textures/MaleZombie/attack_combined.png", "ATTACKtex"))
		std::cerr << "Failed to load texture: Attack (1).png\n";

	if (!texGraphics->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "WALKtex"))
		std::cerr << "Failed to load texture: WALK (1).png\n";


	texGraphics->createSprite("Player");

	texGraphics->AddAnimationSet("IDLE", "Player",
		AnimationData{ "IDLEtex",  5, 60, 62 });

	texGraphics->AddAnimationSet("ATTACK", "Player",
		AnimationData{ "ATTACKtex", 8,  432, 521 });

	texGraphics->AddAnimationSet("WALK", "Player",
		AnimationData{ "WALKtex", 5,  60, 62 });


}

void Character::up()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		y -= yspeed;
		moving = true;
		texGraphics->RenderSprite("Player", sf::Vector2f(x, y), "WALK", 0);
	}
}

void Character::down()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		y += yspeed;
		moving = true;
		texGraphics->RenderSprite("Player", sf::Vector2f(x, y), "WALK", 0);
	}
}

void Character::left()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		x -= xspeed;
		moving = true;
		texGraphics->RenderSprite("Player", sf::Vector2f(x, y), "WALK", 0);
	}
}

void Character::right()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		x += xspeed;
		moving = true;
		texGraphics->RenderSprite("Player", sf::Vector2f(x, y), "WALK", 0);
		
	}
}

void Character::move()
{
	texGraphics->RenderSprite("Player", sf::Vector2f(x, y), "IDLE", 0);
	moving = false;
	up();
	down();
	left();
	right();
}



