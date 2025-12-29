#include "level.h"

void level::load(const char map[8][17], float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio)
{
    tiles.clear();
	bgtiles.clear();
	bgSpriteName = bgName;

	audio->PlayMusic(musicName);

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (map[y][x] == '#')
            {
                sf::RectangleShape tile;
                tile.setSize({ tileSize, tileSize });
                tile.setPosition({ x * tileSize, y * tileSize });
                tile.setTexture(&loadtex->getTexture("Tileset"));

                tiles.push_back(tile);
            }

            if (map[y][x] == '.')
            {
                sf::RectangleShape bgtile;
                bgtile.setSize({ tileSize, tileSize });
                bgtile.setPosition({ x * tileSize, y * tileSize });
                bgtile.setTexture(&loadtex->getTexture("Tilesetbg"));

                bgtiles.push_back(bgtile);
            }
        }
    }
}

void level::draw(sf::RenderWindow& window, Graphics* loadtex)
{
    loadtex->RenderSprite("Level_Background", sf::Vector2f(-300.f, 0.f), "Background", 0);
    for (auto& bgtile : bgtiles)
    {
        window.draw(bgtile);
    }
    for (auto& tile : tiles)
    {
        window.draw(tile);
    }
    
   
}

const std::vector<sf::RectangleShape>& level::getTiles() const
{
    return tiles;
}