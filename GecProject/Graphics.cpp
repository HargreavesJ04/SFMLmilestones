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
			delete texture;
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
	return true;
}


bool Graphics::AddAnimationSet(const std::string& setName, const std::string& spriteName, const AnimationData& setData)
{
	if (m_texturemap.find(setData.textureName) == m_texturemap.end())
	{
		return false;
	}

	m_spritemap[spriteName]->AddAnimationSet(setName, setData, m_texturemap[setData.textureName]);
	return true;
}


void Graphics::SetSpriteColour(const std::string& spriteName, const sf::Color& colour)
{
	if (m_spritemap.count(spriteName))
	{
		m_spritemap[spriteName]->SetColour(colour);
	}
}


void Graphics::SetSpriteFlip(const std::string& spriteName, bool flip)
{
	if (m_spritemap.count(spriteName))
	{
		Sprite2D* s = m_spritemap[spriteName];

		if (flip)
		{
			s->sprite->setScale({ -1.f, 1.f });
		}
		else
		{
			s->sprite->setScale({ 1.f, 1.f });
		}
	}
}


void Graphics::RenderSprite(const std::string& spriteName, sf::Vector2f pos, const std::string& spriteSetName, int frameNum)
{
	if (m_spritemap.find(spriteName) == m_spritemap.end() || m_spritemap[spriteName]->m_animationData.find(spriteSetName) == m_spritemap[spriteName]->m_animationData.end())
	{
		return;
	}

	Sprite2D* briefName = m_spritemap[spriteName];
	briefName->sprite->setTexture(*briefName->m_animationData[spriteSetName].texture);

	int frameX = (int)briefName->m_animationData[spriteSetName].texture->getSize().x;
	int frameY = (int)briefName->m_animationData[spriteSetName].texture->getSize().y / briefName->m_animationData[spriteSetName].setData.numFrames;
	int topCorner = frameY * briefName->frameNumber;

	briefName->sprite->setTextureRect(sf::IntRect({ 0 , topCorner }, { frameX, frameY }));
	briefName->sprite->setOrigin({ (float)frameX / 2.f, (float)frameY / 2.f });
	briefName->sprite->setPosition(pos);

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


sf::Texture& Graphics::getTexture(std::string name)
{
	return *m_texturemap[name];
}