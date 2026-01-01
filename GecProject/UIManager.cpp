#include "UIManager.h"

void UIManager::drawDeathScreen(sf::RenderWindow& window, sf::Texture& texture, sf::Font& font)
{
	sf::Sprite background(texture);
	window.draw(background);

	sf::Text text(font);
	text.setString("Press R to Restart");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f, textBounds.position.y + textBounds.size.y / 2.0f });
	text.setPosition({ 400.f, 300.f });

	sf::RectangleShape textBox;
	textBox.setSize({ textBounds.size.x + 20.f, textBounds.size.y + 10.f });
	textBox.setFillColor(sf::Color::Black);
	textBox.setOrigin({ textBox.getSize().x / 2.0f, textBox.getSize().y / 2.0f });
	textBox.setPosition(text.getPosition());

	window.draw(textBox);
	window.draw(text);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		restartRequested = true;
	}
}

void UIManager::drawVictoryScreen(sf::RenderWindow& window, sf::Texture& texture, sf::Font& font)
{
	sf::Sprite background(texture);
	window.draw(background);

	sf::RectangleShape nextBtn({ 200.f, 60.f });
	nextBtn.setPosition({ 300.f, 400.f });
	nextBtn.setFillColor(sf::Color::Black);

	sf::RectangleShape quitBtn({ 200.f, 60.f });
	quitBtn.setPosition({ 300.f, 480.f });
	quitBtn.setFillColor(sf::Color::Black);

	window.draw(nextBtn);
	window.draw(quitBtn);

	sf::Text nextText(font);
	nextText.setString("Next Level");
	nextText.setCharacterSize(25);
	nextText.setPosition({ 335.f, 415.f });
	window.draw(nextText);

	sf::Text quitText(font);
	quitText.setString("Quit Game");
	quitText.setCharacterSize(25);
	quitText.setPosition({ 340.f, 495.f });
	window.draw(quitText);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (isButtonClicked(nextBtn, window))
		{
			nextLevelClicked = true;
		}
		if (isButtonClicked(quitBtn, window))
		{
			window.close();
		}
	}
}

bool UIManager::isButtonClicked(sf::RectangleShape& button, sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	return button.getGlobalBounds().contains(worldPos);
}