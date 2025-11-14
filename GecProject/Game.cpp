#include "Game.h"

Game::Game()
{
    this->initWindow();
    this->initGraphics();
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

void Game::initGraphics()
{
    

    if (!texGraphics->loadTexture("Data/Textures/MaleZombie/idle_combined.png", "IDLEtex"))
        std::cerr << "Failed to load texture: Idle (1).png\n";

    if (!texGraphics->loadTexture("Data/Textures/MaleZombie/attack_combined.png", "ATTACKtex"))
        std::cerr << "Failed to load texture: Attack (1).png\n";

    if (!texGraphics->loadTexture("Data/Textures/MaleZombie/walk_combined.png", "WALKtex"))
        std::cerr << "Failed to load texture: WALK (1).png\n";


    texGraphics->createSprite("Player");

    texGraphics->AddAnimationSet("IDLE", "Player",
        AnimationData{ "IDLEtex",  15, 432, 521 });

    texGraphics->AddAnimationSet("ATTACK", "Player",
        AnimationData{ "ATTACKtex", 8,  432, 521 }); 

    texGraphics->AddAnimationSet("WALK", "Player",
        AnimationData{ "WALKtex", 10,  432, 521 });

   
}

void Game::updateSFML()
{
    
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

    if (player.moving == false)
    {
        texGraphics->RenderSprite("Player", sf::Vector2f(player.x, player.y), "IDLE", 0);
    }
    else if (player.moving == true)
    {
        texGraphics->RenderSprite("Player", sf::Vector2f(player.x, player.y), "WALK", 0);
    }

    
	
    texGraphics->Draw(*this->window); 

    this->window->display(); 
    sf::sleep(time);

    player.moving = false;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->UpdateDt();
        this->updateEvents();
        this->updateSFML();
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
