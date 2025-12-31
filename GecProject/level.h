#pragma once
#include <vector>
#include <string>
#include "Graphics.h"
#include "Audio.h"
#include <fstream>
#include "SFML/Graphics/View.hpp"
#include "Enemy.h"


class level
{
public:

    level();
    ~level();

    sf::Vector2f load(std::string fileName, float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio, std::unordered_map<std::string, Enemy*>& enemyMap);
    void draw(sf::RenderWindow& window, Graphics* loadtex);
    const std::vector<sf::RectangleShape>& getTiles() const;

    sf::View miniView;
    sf::Sprite* miniMapFrame = nullptr;
    
private:
    std::vector<sf::RectangleShape> tiles;
	std::vector<sf::RectangleShape> bgtiles;
	std::string bgSpriteName;
  
};