#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <iostream>
#include "Character.h"
#include "Collision.h"


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
    void initGraphics();     


    sf::RenderWindow* window = nullptr;
    std::optional<sf::Event> sfEvent;

    float deltaTime = 0.f;
    sf::Clock dtClock;

	Graphics* texGraphics = new Graphics; 
    sf::Time time = sf::milliseconds(50);
    Character player;
   // Collision box;
};


