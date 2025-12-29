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
    
	Alucard.update(deltaTime, test);
	enemy.move();

    if (Alucard.CheckCollision(enemy))
    {
		Alucard.takeDamage(30);
    }

    sf::View view;
    view.setSize({ 400.f, 300.f });
    view.setCenter(Alucard.position);
    this->window->setView(view);

    test.draw(*this->window, loadtex);
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
    loadtex->loadTexture("Data/Textures/Tilesets/dirt.png", "Tileset");
    loadtex->loadTexture("Data/Textures/Tilesets/dirt2.png", "Tilesetbg");
    //test level
	test.load(charMap, 32.f, loadtex, "Level_Background", "Data/Audio/Vampire-Killer.wav", audio);

    loadtex->loadTexture("Data/Textures/Background/Background.png", "Backgroundtex");
    loadtex->createSprite("Level_Background");
    loadtex->AddAnimationSet("Background", "Level_Background", AnimationData{ "Backgroundtex", 1 });

    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "IDLEtex");
    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "ATTACKtex");
    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "WALKtex");
    loadtex->createSprite("Player");

    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EIDLEtex");
    loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EWALKtex");
    loadtex->createSprite("Enemy");
}

	


void Game::initAudio()
{
    audio->SetMusicVolume(15.f);
}

void Game::initWindow()
{

    this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }),  "GEC Start Project [Totally Not Catlevania]" );
}
