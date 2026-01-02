#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"

class HUD
{
public:
	HUD();
	~HUD();

	void initGraphics(Graphics* graphics);
	void update(int currentHealth, int maxHealth);
	void draw(sf::RenderWindow& window);

private:
	sf::Sprite* barFrame = nullptr;
	sf::RectangleShape* healthBar;
	float maxBarWidth;
};