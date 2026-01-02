#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <iostream>




class UIManager
{
public:
	UIManager();
	~UIManager();

	void drawDeathScreen(sf::RenderWindow& window);
	void drawVictoryScreen(sf::RenderWindow& window);

	void initGraphics(Graphics* graphics);

	bool nextLevelClicked = false;
	bool restartRequested = false;

private:

	sf::Texture* deathTex = nullptr;
	sf::Texture* winTex = nullptr;
	sf::Font gameFont;
	bool isButtonClicked(sf::RectangleShape& button, sf::RenderWindow& window);


};

