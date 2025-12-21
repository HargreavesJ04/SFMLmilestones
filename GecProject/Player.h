#pragma once
#include "Character.h"
class Player : public Character
{
public: 

	void move();
	void update(float dt, const int* levelData);
	void initGraphics(Graphics* texGraphics) override; 
	void initAudio(Audio* audio) override;
	void takeDamage(int damage) override;
	bool checkLevelCollision(const int* tiles, unsigned int width, unsigned int height, sf::Vector2u tileSize);

private:

	float deltaTime = 0.f;
	float lastFrame = deltaTime - 10.f;
	float Iframes = 0.f;
	std::string setState(Movement state);
};

