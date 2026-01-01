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
	auto& animation = briefName->m_animationData[spriteSetName];

	briefName->sprite->setTexture(*animation.texture);

	int frameX = (int)animation.texture->getSize().x;
	int frameY = (int)animation.texture->getSize().y / animation.setData.numFrames;
	int topCorner = frameY * briefName->frameNumber;

	briefName->sprite->setTextureRect(sf::IntRect({ 0, topCorner }, { frameX, frameY }));

	if (briefName->sprite->getScale().x < 0)
	{
		briefName->sprite->setOrigin({ (float)frameX, 0.f });
	}
	else
	{
		briefName->sprite->setOrigin({ 0.f, 0.f });
	}

	briefName->sprite->setPosition(pos);

	if (briefName->frameNumber < animation.setData.numFrames - 1)
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