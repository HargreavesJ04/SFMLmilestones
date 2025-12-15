#pragma once


#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "level.h" 


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
    
private:
    void initWindow();       
         


    sf::RenderWindow* window = nullptr;
    std::optional<sf::Event> sfEvent;

    float deltaTime = 0.f;
    sf::Clock dtClock;
    sf::Time time = sf::milliseconds(50);

    Graphics* loadtex = new Graphics();

	
    sf::Music music;
	Player Alucard;
	Enemy enemy;
    level test;
};


