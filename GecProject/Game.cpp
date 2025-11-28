#include "Game.h"

Collision box;

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
    
	box.colliderX = 200;
    box.colliderY = 200;
    box.colliderWidth = 432;
    box.colliderHeight = 521;

   /* if (!player.texGraphics->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "IDLEtex"))
        std::cerr << "Failed to load texture: Idle (1).png\n";

    if (!player.texGraphics->loadTexture("Data/Textures/MaleZombie/attack_combined.png", "ATTACKtex"))
        std::cerr << "Failed to load texture: Attack (1).png\n";

    if (!player.texGraphics->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "WALKtex"))
        std::cerr << "Failed to load texture: WALK (1).png\n";


    player.texGraphics->createSprite("Player");

    player.texGraphics->AddAnimationSet("IDLE", "Player",
        AnimationData{ "IDLEtex",  5, 60, 62 });

    player.texGraphics->AddAnimationSet("ATTACK", "Player",
        AnimationData{ "ATTACKtex", 8,  432, 521 }); 

    player.texGraphics->AddAnimationSet("WALK", "Player",
        AnimationData{ "WALKtex", 5,  60, 62 });*/

   
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


    /*if (player.moving == false)
    {
        player.texGraphics->RenderSprite("Player", sf::Vector2f(player.x, player.y), "IDLE", 0);
    }
    else if (player.moving == true)
    {
      
        
		
    }*/

    
	
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
