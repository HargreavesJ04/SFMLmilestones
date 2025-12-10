#include "Game.h"



Game::Game()
{
    initWindow();
	player.initGraphics();
    
	enemy.initEnemyGraphics();
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

    enemy.box.Move(enemy.position);

    player.box.CheckCollision(enemy.box.GetBox());

    sf::View view;
    view.setSize({ 400.f, 300.f });
    view.setCenter(player.position);
    this->window->setView(view);

    player.texGraphics->Draw(*this->window);
    enemy.texGraphics->Draw(*this->window);

    this->window->display();
    sf::sleep(time);
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
    

    this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }),  "GEC Start Project [Totally Not Catlevania]" );
}
