#include "Game.h"




Game::Game()
{

    if (music.openFromFile("Data/Audio/Vampire-Killer.wav"))
    {
        music.setVolume(50); 
        music.setLooping(true); 
        music.play();
    }

    initWindow();
	initGraphics();
	Alucard.initGraphics(loadtex);
	enemy.initGraphics(loadtex);
}

Game::~Game()
{
    delete this->window;
    delete this->loadtex;
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

void Game::initWindow()
{
    
   
    this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }),  "GEC Start Project [Totally Not Catlevania]" );
}
