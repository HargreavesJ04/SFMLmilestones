#pragma once
#include <SFML/Graphics.hpp>

enum class GameState
{
	Playing,
	GameOver,
	Paused,
	Win
};


class GameManager
{
public:

	GameManager();

	void update(int playerHealth, bool reachedWinTile);
	void handleInput(sf::Keyboard::Key key);

	GameState getState() { return currentState; }
	bool shouldReset() { return needsReset; }
	void clearResetFlag() { needsReset = false; }

private:
	GameState currentState;
	bool needsReset;
};