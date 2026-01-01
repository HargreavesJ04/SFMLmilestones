#include "GameManager.h"

GameManager::GameManager()
{
	currentState = GameState::Playing;
	needsReset = false;
}

void GameManager::update(int playerHealth, bool reachedWinTile)
{
	if (playerHealth <= 0)
	{
		currentState = GameState::GameOver;
	}
	else if (reachedWinTile)
	{
		currentState = GameState::Win;
	}
	else
	{
		currentState = GameState::Playing;
	}
}

void GameManager::handleInput(sf::Keyboard::Key key)
{
	if (currentState == GameState::GameOver && key == sf::Keyboard::Key::R)
	{
		needsReset = true;
	}

	if (currentState == GameState::Win)
	{
		if (key == sf::Keyboard::Key::Enter)
		{
			needsReset = true;
		}
	}
}