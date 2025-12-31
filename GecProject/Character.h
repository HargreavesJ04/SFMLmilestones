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
protected:

	Collision box{{position,size} };
	Graphics* texGraphics = nullptr;
	Audio* sfxaudio = nullptr;
	Movement currentState = Idle;
	
	//these dont do anything yet :/
//	int health = 100;
};

