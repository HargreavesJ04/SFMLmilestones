#pragma once
#include "Entity.h"
#include "graphics.h"
#include "Collision.h"
#include "Audio.h"


class Character : public Entity
{
public:

	enum Movement
	{
		Idle,
		Jump,
		Crouch,
		Left,
		Right,
		Falling,
		Attack,
		Dead
	};

	virtual void initGraphics(Graphics* graphics);
	virtual void initAudio(Audio* audio);

	virtual void takeDamage(int damage);
	bool CheckCollision(Character& other);

	void playSound(const std::string& name);
	void playSoundLooped(const std::string& name);
	void stopSound(const std::string& name);

	bool moving = false;
	bool movingBack = false;
	bool airborne;
	float xspeed = 5.f;
	float yspeed = 5.f;
	int health = 100;

	bool isAttacking = false;
	float attackTimer = 0.0f;
	float damageFlashTimer = 0.0f;

	Collision box{ {position,size} };

protected:

	Graphics* texGraphics = nullptr;
	Audio* sfxaudio = nullptr;
	Movement currentState = Idle;

};