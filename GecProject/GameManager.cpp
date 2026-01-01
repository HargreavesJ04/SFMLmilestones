#include "GameManager.h"


GameManager::GameManager()
{
    currentState = GameState::Playing;
    needsReset = false;
}

void GameManager::update(int playerHealth, bool reachedWinTile)
{
    if (currentState == GameState::Playing) {
        if (playerHealth <= 0) {
            currentState = GameState::GameOver;
        }
        else if (reachedWinTile) {
            currentState = GameState::Win;
        }
    }
}

void GameManager::handleInput(sf::Keyboard::Key key) 
{
    if (currentState == GameState::GameOver && key == sf::Keyboard::Key::R)
    {
        needsReset = true;
        currentState = GameState::Playing;
    }

    if (currentState == GameState::Win) {
        if (key == sf::Keyboard::Key::Enter) {
            needsReset = true;
            currentState = GameState::Playing;
        }
    }
}