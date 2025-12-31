#include "Game.h"

Game::Game()
{
	initWindow();
	initGraphics();
	initAudio();

	playerHUD = new HUD();

	Alucard.initGraphics(loadtex);
	Alucard.initAudio(audio);

	Alucard.position = test.load("Data/Levels/Level1.txt", 32.f, loadtex, "Level_Background", "Data/Audio/Vampire-Killer.wav", audio, enemies);
}

Game::~Game()
{
	for (auto& pair : enemies)
	{
		delete pair.second;
	}
	enemies.clear();

	delete this->window;
	delete this->loadtex;
	delete this->audio;
	delete this->playerHUD;
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

void Game::render() {
	this->window->clear();

	Alucard.update(deltaTime, test, enemies);

	for (auto const& [name, e] : enemies)
	{
		e->move(deltaTime, test);

		if (Alucard.CheckCollision(*e))
		{
			Alucard.takeDamage(10);
		}
	}

	sf::View mainView;
	mainView.setSize({ 400.f, 300.f });
	mainView.setCenter(Alucard.position);
	this->window->setView(mainView);

	test.draw(*this->window, loadtex);
	loadtex->Draw(*this->window);

	test.miniView.setCenter(Alucard.position);
	this->window->setView(test.miniView);

	test.draw(*this->window, loadtex);
	loadtex->Draw(*this->window);

	this->window->setView(this->window->getDefaultView());

	playerHUD->update(Alucard.health, 200);
	playerHUD->draw(*this->window);

	this->window->display();
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

	loadtex->loadTexture("Data/Textures/Background/Background.png", "Backgroundtex");
	loadtex->createSprite("Level_Background");
	loadtex->AddAnimationSet("Background", "Level_Background", AnimationData{ "Backgroundtex", 1 });

	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "IDLEtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "ATTACKtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "WALKtex");
	loadtex->createSprite("Player");

	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EIDLEtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EWALKtex");
}

void Game::initAudio()
{
	audio->SetMusicVolume(15.f);
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }), "GEC Project");
	this->window->setFramerateLimit(20);
}