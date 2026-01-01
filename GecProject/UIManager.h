#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>




class UIManager
{
public:

	void drawDeathScreen(sf::RenderWindow& window, sf::Texture& texture, sf::Font& font);
	void drawVictoryScreen(sf::RenderWindow& window, sf::Texture& texture, sf::Font& font);

	bool nextLevelClicked = false;
	bool restartRequested = false;

private:

	bool isButtonClicked(sf::RectangleShape& button, sf::RenderWindow& window);


};

