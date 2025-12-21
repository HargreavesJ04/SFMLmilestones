#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Collision.h"

class level : public sf::Drawable, public sf::Transformable
{
public:
	std::string* levelfile;
	void loadfromfile(std::string filepath);

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	Collision box;
};