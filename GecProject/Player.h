#pragma once
#include "Character.h"
#include "level.h"


class Player : public Character
{
public:

	

	void move();
	void update(float dt, const level& map, std::unordered_map<std::string, class Enemy*>& enemies);
	void initGraphics(Graphics* texGraphics) override;
	void initAudio(Audio* audio) override;
	void takeDamage(int damage) override;

	int score = 0;

private:

	bool grounded = false;
	float gravity = 1.0f;
	float Iframes = 0.f;
	int faceDir = 1;



	std::string setState(Movement state);
};