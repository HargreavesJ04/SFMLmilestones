#pragma once
#include <vector>
#include <string>
#include "Graphics.h"
#include "Audio.h"


class level
{
public:
    void load(const char map[8][17], float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio);
    void draw(sf::RenderWindow& window, Graphics* loadtex);
    const std::vector<sf::RectangleShape>& getTiles() const;

private:
    std::vector<sf::RectangleShape> tiles;
	std::vector<sf::RectangleShape> bgtiles;
	std::string bgSpriteName;
};