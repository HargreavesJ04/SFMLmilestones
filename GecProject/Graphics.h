#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "AnimationData.h"


class Sprite2D; 

class Graphics
{
private: 

	

public: 
	bool loadTexture(const std::string& filename, const std::string& name); 
	bool createSprite(const std::string& name);
	bool AddAnimationSet(const std:: string&  setName, const std::string& spriteName ,const AnimationData& setData );

	void RenderSprite(const std::string& spriteName, sf::Vector2f pos, const std::string& spriteSetName, int frameNum);
	void Draw(sf::RenderWindow& window);

	std::unordered_map<std::string, Sprite2D*> m_spritemap;
	std::unordered_map<std::string, sf::Texture*> m_texturemap;
};

