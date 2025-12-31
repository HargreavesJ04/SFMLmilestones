#include "HUD.h"

HUD::HUD()
{
	healthBarBack = new sf::RectangleShape(sf::Vector2f(200.f, 20.f));
	healthBarBack->setFillColor(sf::Color(100, 0, 0));

	healthBarFront = new sf::RectangleShape(sf::Vector2f(200.f, 20.f));
	healthBarFront->setFillColor(sf::Color::Red);
}

HUD::~HUD()
{
	delete healthBarBack;
	delete healthBarFront;
}

void HUD::update(int currentHealth, int maxHealth)
{
	float healthPercent = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);

	if (healthPercent < 0.f) healthPercent = 0.f; //clamp to 0 so it wont go negative 

	healthBarFront->setScale({ healthPercent, 1.f }); 
}

void HUD::draw(sf::RenderWindow& window)
{
	sf::View oldView = window.getView();
	window.setView(window.getDefaultView());

	healthBarBack->setPosition({ 10.f, 10.f });
	healthBarFront->setPosition({10.f, 10.f});

	window.draw(*healthBarBack);
	window.draw(*healthBarFront);
	window.setView(oldView);
}

