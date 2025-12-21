#include "Sprite2D.h"

void Sprite2D::SetColour(const sf::Color& colour)
{
	sprite->setColor(colour);
}

void Sprite2D::AddAnimationSet(const std::string& name, const AnimationData& setData, sf::Texture* texture)

{
	if (m_animationData.find(name) == m_animationData.end())
	{

		m_animationData[name] = AnimationSet(setData, texture);

		if (sprite == nullptr)
		{
			sprite = new sf::Sprite(*texture);
		}
	}
}
