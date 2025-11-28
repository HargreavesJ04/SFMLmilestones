#include "Game.h"

Collision box;

Game::Game()
{
    this->initWindow();
    this->initBox();
	player.initGraphics();
}

Game::~Game()
{
    delete this->window;
}

void Game::endApplication()
{
   
}

void Game::UpdateDt()
{
    this->deltaTime = this->dtClock.restart().asSeconds();
}

void Game::initBox()
{
    
	box.colliderX = 200;
    box.colliderY = 200;
    box.colliderWidth = 432;
    box.colliderHeight = 521;


   
}


void Game::updateEvents()
{
    
    while (this->sfEvent = this->window->pollEvent())
    {
        if (sfEvent->is<sf::Event::Closed>())
            this->window->close();
		

		
		
    }
}

void Game::render()
{
    this->window->clear();
    
    

	player.move(); 

	
   player.texGraphics->Draw(*this->window); 

    this->window->display(); 
    sf::sleep(time);
    box.CheckCollision(player);
    player.moving = false;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->UpdateDt();
        this->updateEvents();
        this->render();
		
    }
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode({ 800, 600 }),
        "GEC Start Project"
    );
}
