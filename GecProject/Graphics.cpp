#include "Graphics.h"
#include "Sprite2D.h"
#include <iostream>

bool Graphics::loadTexture(const std::string& filename, const std::string& name)
{
	if (m_texturemap.find(name) == m_texturemap.end())
	{
	

		sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(filename))
		{
			return false;
		}

		m_texturemap[name] = texture;
		return true;
	}


	return false;
}

bool Graphics::createSprite(const std::string& name)
{
	Sprite2D* newSprite = new Sprite2D; 



	m_spritemap[name] = newSprite;

	return false;
}

bool Graphics::AddAnimationSet(const std::string& setName, const std::string& spriteName, const AnimationData& setData)
{
	if (m_texturemap.find(setData.textureName) == m_texturemap.end())
	{


		return false;
	}

	m_spritemap[spriteName]->AddAnimationSet(setName, setData, m_texturemap[setData.textureName]);


	return false;
}

void Graphics::RenderSprite(const std::string& spriteName, sf::Vector2f pos, const std::string& spriteSetName, int frameNum)
{
	if (m_spritemap.find(spriteName) == m_spritemap.end() || m_spritemap[spriteName]->m_animationData.find(spriteSetName) == m_spritemap[spriteName]->m_animationData.end())
	{
		std::cout << "Sprite not found" << std::endl;
	}

	Sprite2D* briefName = m_spritemap[spriteName];

	if (briefName == nullptr) {
		std::cerr << "Sprite2D object for '" << spriteName << "' is null." << std::endl;
		return;
	}

	briefName->sprite->setTexture(*briefName->m_animationData[spriteSetName].texture);

	briefName->sprite->setPosition(pos);

	int frameX = briefName->m_animationData[spriteSetName].texture->getSize().x;
	int frameY = briefName->m_animationData[spriteSetName].texture->getSize().y / briefName->m_animationData[spriteSetName].setData.numFrames;
	int topCorner = frameY * briefName->frameNumber;
	briefName->sprite->setTextureRect(sf::IntRect({ 0 , topCorner }, { frameX, frameY })); 
	
	

	
	if (briefName->frameNumber < briefName->m_animationData[spriteSetName].setData.numFrames - 1)
	{
		briefName->frameNumber++;
	}
	else
	{
		briefName->frameNumber = 0;
	}

	
}




void Graphics::Draw(sf::RenderWindow& window)
{
	for (auto& i : m_spritemap)
	{
		if (i.second->sprite != nullptr)
		{
			window.draw(*i.second->sprite);
		}
	}
}