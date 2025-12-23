#include "level.h"

void level::load(const char map[8][17], float tileSize, Graphics* loadtex)
{
    m_tiles.clear();

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

                m_tiles.push_back(tile);
            }

            if (map[y][x] == '.')
            {
                sf::RectangleShape bgtile;
                bgtile.setSize({ tileSize, tileSize });
                bgtile.setPosition({ x * tileSize, y * tileSize });
                bgtile.setTexture(&loadtex->getTexture("Tilesetbg"));

                m_tiles.push_back(bgtile);
            }
        }
    }
}

void level::draw(sf::RenderWindow& window)
{
    for (auto& tile : m_tiles)
    {
        window.draw(tile);
    }
}

const std::vector<sf::RectangleShape>& level::getTiles() const
{
    return m_tiles;
}