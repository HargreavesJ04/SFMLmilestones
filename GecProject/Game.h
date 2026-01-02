#pragma once

#include "Player.h"
#include "Enemy.h"
#include "level.h" 
#include "Audio.h"
#include "HUD.h"
#include "GameManager.h"
#include "UIManager.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void UpdateDt();
    void updateEvents();
    void render();
    void run();
    void initGraphics();
    void initAudio();

private:
    void initWindow();

    sf::RenderWindow* window = nullptr;
    std::optional<sf::Event> sfEvent;

    float deltaTime = 0.f;
    sf::Clock dtClock;
    sf::Time time = sf::milliseconds(50);

    Graphics* loadtex = new Graphics();
    Audio* audio = new Audio();

    std::unordered_map<std::string, Enemy*> enemies;
    //sf::Music music;
    Player Alucard;
    Enemy enemy;
    HUD* playerHUD;

    GameManager manager;
    UIManager uiManager;
    bool hitWinTile = false;

    level test;

    std::vector<std::string> levels;
    int currentLevelIndex;

    sf::Texture deathTex;
    sf::Texture winTex;
    sf::Font gameFont;
};