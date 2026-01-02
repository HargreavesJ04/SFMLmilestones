#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Graphics.h"
#include "Audio.h"
#include "healthItem.h"

class level
{
public:

	level();
	~level();

	sf::Vector2f load(std::string fileName, float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio, std::unordered_map<std::string, class Enemy*>& enemyMap, std::vector<class healthItem*>& items);
	void draw(sf::RenderWindow& window, Graphics* loadtex);

	const std::vector<sf::RectangleShape>& getTiles() const;
	bool checkWinCondition(sf::FloatRect playerBox);

private:

	std::vector<sf::RectangleShape> tiles;
	std::vector<sf::RectangleShape> bgtiles;
	std::string bgSpriteName;

	sf::View miniView;
	sf::Sprite* miniMapFrame = nullptr;
};