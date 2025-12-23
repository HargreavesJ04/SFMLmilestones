#pragma once
#include "Character.h"
#include "level.h"

class Player : public Character
{
public: 

	void move();
	void update(float dt, const level& map);
	void initGraphics(Graphics* texGraphics) override; 
	void initAudio(Audio* audio) override;
	void takeDamage(int damage) override;

private:

	float gravity = 1.0f;
	float deltaTime = 0.f;
	float lastFrame = deltaTime - 10.f;
	float Iframes = 0.f;
	std::string setState(Movement state);
};

