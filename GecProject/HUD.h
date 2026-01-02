#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <string>

class HUD
{
public:
	HUD();
	~HUD();

	void initGraphics(Graphics* graphics);
	void update(int currentHealth, int maxHealth, int currentScore);
	void draw(sf::RenderWindow& window);

private:
	sf::Sprite* barFrame = nullptr;
	sf::RectangleShape* healthBar;
	float maxBarWidth;

	sf::Font hudFont;
	sf::Text* scoreText = nullptr;
};