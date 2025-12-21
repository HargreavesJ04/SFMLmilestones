#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

class level : public sf::Drawable, public sf::Transformable {
public:
    bool load(const sf::Texture& texture, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    const sf::Texture* m_tileset;
};