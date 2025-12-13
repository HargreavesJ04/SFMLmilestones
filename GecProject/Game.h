#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Sprite2D.h"
#include "Enemy.h"
#include "level.h" 


class Game
{
public:
    Game();
    virtual ~Game();

    void endApplication();   
    void UpdateDt();        
    void updateEvents();          
    void render();          
    void run();             
    
private:
    void initWindow();       
         


    sf::RenderWindow* window = nullptr;
    std::optional<sf::Event> sfEvent;

    float deltaTime = 0.f;
    sf::Clock dtClock;

	
    sf::Time time = sf::milliseconds(50);
    Character player;
	Enemy enemy;
    level test;
};


