#include "Game.h"




Game::Game()
{
    initWindow();
	initGraphics();
	initAudio();

	Alucard.initGraphics(loadtex);
    Alucard.initAudio(audio);

	enemy.initGraphics(loadtex);
}

Game::~Game()
{
    delete this->window;
    delete this->loadtex;
	delete this->audio;
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

    loadtex->RenderSprite("Level_Background", sf::Vector2f(-300.f, 0.f), "Background", 0);

	Alucard.update(deltaTime);
	enemy.move();

    if (Alucard.CheckCollision(enemy))
    {
		Alucard.takeDamage(30);
    }
   
    sf::View view;
    view.setSize({ 400.f, 300.f });
    view.setCenter(Alucard.position);
    this->window->setView(view);

    loadtex->Draw(*this->window);
   
    

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

void Game::initGraphics()
{
    loadtex->loadTexture("Data/Textures/Tilesets/vertex-array-tilemap-tileset.png", "Tilesettex");
 

    loadtex->loadTexture("Data/Textures/Background/Background.png", "Backgroundtex"); 
    loadtex->createSprite("Level_Background");
    loadtex->AddAnimationSet("Background", "Level_Background", AnimationData{ "Backgroundtex",1 });

    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png","IDLEtex");
    loadtex->loadTexture("Data/Textures/MaleZombie/attack_combined.png","ATTACKtex");
    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png","WALKtex");
	
	loadtex->createSprite("Player");

    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png","EIDLEtex");
    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png","EWALKtex");
	
	loadtex->createSprite("Enemy");

	
}

void Game::initAudio()
{
    audio->PlayMusic("Data/Audio/Vampire-Killer.wav");
    audio->SetMusicVolume(50.f);
}

void Game::initWindow()
{
    
   
    this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }),  "GEC Start Project [Totally Not Catlevania]" );
}
