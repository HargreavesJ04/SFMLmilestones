#include "HUD.h"


HUD::HUD()
{
	maxBarWidth = 0.f;
	healthBar = nullptr;
	barFrame = nullptr;
	scoreText = nullptr;
}

HUD::~HUD()
{
	if (healthBar)
	{
		delete healthBar;
	}
	if (barFrame)
	{
		delete barFrame;
	}
	if (scoreText)
	{
		delete scoreText;
	}
}

void HUD::initGraphics(Graphics* graphics)
{
	const sf::Texture& tex = graphics->getTexture("HUDtex");
	barFrame = new sf::Sprite(tex);

	barFrame->setPosition({ 20.f, 0.f });
	barFrame->setScale({3.f, 3.f});

	healthBar = new sf::RectangleShape();
	healthBar->setPosition({ 110.f, 75.f });
	healthBar->setFillColor(sf::Color(180, 0, 0));

	maxBarWidth = 75.f * 2.f;
	healthBar->setSize({ maxBarWidth, 13.f * 2.f });

	if (hudFont.openFromFile("Data/Fonts/SymphonyoftheNightfont.ttf"))
	{
		scoreText = new sf::Text(hudFont);
		scoreText->setCharacterSize(25);
		scoreText->setFillColor(sf::Color::White);
		scoreText->setPosition({ 110.f, 110.f });
		scoreText->setString("Score 0");
	}
}

void HUD::update(int currentHealth, int maxHealth, int currentScore)
{
	if (maxHealth <= 0 || !healthBar) return;

	float hpPercent = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);

	if (hpPercent < 0) hpPercent = 0;

	healthBar->setSize({ maxBarWidth * hpPercent, healthBar->getSize().y });

	
	
	scoreText->setString("Score " + std::to_string(currentScore));
	
}

void HUD::draw(sf::RenderWindow& window)
{
	if (barFrame) window.draw(*barFrame);
	if (healthBar) window.draw(*healthBar);
	if (scoreText) window.draw(*scoreText);
}