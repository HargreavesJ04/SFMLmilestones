#pragma once

#include "Player.h"
#include "Enemy.h"
#include "level.h" 
#include "Audio.h"


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
	
    sf::Music music;
	Player Alucard;
	Enemy enemy;
    level test;

    int levelData[128] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       
    };
};


