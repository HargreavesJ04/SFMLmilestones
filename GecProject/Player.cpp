#include "Player.h"
#include "Enemy.h"



void Player::move()
{
	Movement previousState = currentState;
	currentState = Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && grounded)
	{
		grounded = false;
		position.y -= yspeed * 16;
		currentState = Jump;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		position.x -= xspeed;
		currentState = Left;
		faceDir = -1;
		texGraphics->SetSpriteFlip("Player", true);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		position.x += xspeed;
		currentState = Right;
		faceDir = 1;
		texGraphics->SetSpriteFlip("Player", false);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !isAttacking)
	{
		isAttacking = true;
		attackTimer = 0.4f;
		currentState = Attack;
	}
	

	box.Move(position); //similar to sfml documentation getglobal bounds so collision box follows player position

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

	if (texGraphics) //update player anim based on state
	{
		std::string animName = setState(currentState);
		texGraphics->RenderSprite("Player", position, animName, 0);
	}
}

void Player::update(float dt, const level& map, std::unordered_map<std::string, Enemy*>& enemies) 
{
	move();
	box.Move(position);

	if (isAttacking)
	{
		attackTimer -= dt;
		if (attackTimer <= 0.0f)
		{
			isAttacking = false;
		}

		sf::FloatRect attackHitbox;
		float range = 35.0f;

		if (faceDir == 1) //sets players center of origin for flipping 
		{
			attackHitbox = sf::FloatRect({ position.x + 60.f * 0.7f, position.y + 62.f * 0.2f }, { range, 62.f * 0.6f });
		}
		else
		{
			attackHitbox = sf::FloatRect({ position.x - range, position.y + 62.f * 0.2f }, { range, 62.f * 0.6f }); //we love magic numbers
		}

		for (auto const& [name, enemy] : enemies)
		{
			if (attackHitbox.findIntersection(enemy->box.GetBox()))
			{
				bool wasAlive = (enemy->health > 0);
				enemy->takeDamage(20);

				if (wasAlive && enemy->health <= 0)
				{
					score += 500;
				}
			}
		}
	}

	//I check the x and y collisions separately to avoid corner sticking it is based on unity rigid body collision handling

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

	position.y += yspeed * 1.0f; //adds gravity and updates position because if not you will be floating
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
					grounded = true;
				}
				else
				{
					position.y += intersect->size.y;
				}
				box.Move(position);
			}
		}
	}

	//added so player doesnt just die in a couple frames and added visual feedback for taking damage for debugging and overall style 
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

	if (health <= 0) //worlds most jank death handling please dont judge me it was easy 
	{
		position = { -10000.f, -10000.f };
		box.Move(position);
		currentState = Dead;
		return;
	}
}

void Player::initGraphics(Graphics* texGraphics)
{
	Character::initGraphics(texGraphics);

	texGraphics->AddAnimationSet("IDLE", "Player", AnimationData{ "IDLEtex", 16 }); //only need to pass through frames animationData handles the texture size
	texGraphics->AddAnimationSet("ATTACK", "Player", AnimationData{ "ATTACKtex", 16 });
	texGraphics->AddAnimationSet("WALK", "Player", AnimationData{ "WALKtex", 16 });
	texGraphics->AddAnimationSet("CROUCH", "Player", AnimationData{ "WALKtex", 16 });
	texGraphics->AddAnimationSet("JUMP", "Player", AnimationData{ "WALKtex", 16 });
}

void Player::initAudio(Audio* audio)
{
	Character::initAudio(audio);

	audio->LoadSound("ATTACK", "Data/Audio/sfx/Alucard/cutt.wav");
	audio->LoadSound("WALK", "Data/Audio/sfx/Alucard/walk.wav");
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