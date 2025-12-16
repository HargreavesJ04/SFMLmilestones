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

	Alucard.move();
	enemy.move();

    if (Alucard.CheckCollision(enemy))
    {
		audio->PlaySound("HIT");
        std::cout << "Collision Detected!" << std::endl;
		Alucard.takeDamage(1);

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
	audio->LoadSound("HIT", "Data/Audio/sfx/Alucard/alu_aah.wav");

    audio->PlayMusic("Data/Audio/Vampire-Killer.wav");
    audio->SetMusicVolume(50.f);
}

void Game::initWindow()
{
    
   
    this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }),  "GEC Start Project [Totally Not Catlevania]" );
}
