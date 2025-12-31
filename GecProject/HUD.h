#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:

	HUD();
	~HUD();

	void update(int currentHealth, int maxHealth);
	void draw(sf::RenderWindow& window); 


private:
	sf::RectangleShape* healthBarBack;
	sf::RectangleShape* healthBarFront;
};

