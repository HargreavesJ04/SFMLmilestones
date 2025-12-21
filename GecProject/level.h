#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Graphics.h"


class level
{
public:
    void load(const char map[8][17], float tileSize, Graphics* loadtex);
    void draw(sf::RenderWindow& window);
    const std::vector<sf::RectangleShape>& getTiles() const;

private:
    std::vector<sf::RectangleShape> m_tiles;
};