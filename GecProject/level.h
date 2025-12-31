#pragma once
#include <vector>
#include <string>
#include "Graphics.h"
#include "Audio.h"
#include "SFML/Graphics/View.hpp"


class level
{
public:

    level();
    ~level();

    void load(const char map[8][17], float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio);
    void draw(sf::RenderWindow& window, Graphics* loadtex);
    const std::vector<sf::RectangleShape>& getTiles() const;

    sf::View miniView;
    sf::Sprite* miniMapFrame = nullptr;
    
private:
    std::vector<sf::RectangleShape> tiles;
	std::vector<sf::RectangleShape> bgtiles;
	std::string bgSpriteName;
  
};