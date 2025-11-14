#pragma once

#include "AnimationData.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>


struct AnimationSet
{
	AnimationData setData; 
	sf::Texture* texture{ nullptr }; 
};

class Sprite2D
{
public:
	void AddAnimationSet(const std::string& name, const AnimationData& setData, sf::Texture* texture);
	std::unordered_map<std::string, AnimationSet> m_animationData;
	sf::Sprite* sprite = nullptr;

	int frameNumber = 0;

private: 
	 
	
	
};

