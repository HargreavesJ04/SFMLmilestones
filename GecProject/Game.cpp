#include "Game.h"
#include <iostream>

Game::Game()
{
	initWindow();
	initGraphics();
	initAudio();

	playerHUD = new HUD();

	if (!deathTex.loadFromFile("Data/Textures/Background/GameOver.png"))
		std::cout << "Failed to load death texture" << std::endl;

	if (!winTex.loadFromFile("Data/Textures/Background/WinScreen.png"))
		std::cout << "Failed to load win texture" << std::endl;

	if (!gameFont.openFromFile("Data/Fonts/SymphonyoftheNightfont.ttf"))
	{
		std::cout << "Could not load font!" << std::endl;
	}

	levels.push_back("Data/Levels/Level1.txt");
	levels.push_back("Data/Levels/Level1.txt");
	currentLevelIndex = 0;

	Alucard.initGraphics(loadtex);
	Alucard.initAudio(audio);

	Alucard.position = test.load(levels[currentLevelIndex], 32.f, loadtex, "Level_Background", "Data/Audio/Vampire-Killer.wav", audio, enemies);
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

		if (sfEvent->is<sf::Event::KeyPressed>())
		{
			auto key = sfEvent->getIf<sf::Event::KeyPressed>()->code;
			manager.handleInput(key);
		}
	}
}

void Game::render()
{
	this->window->clear();

	if (uiManager.restartRequested)
	{
		Alucard.health = 100;
		Alucard.position = test.load(levels[currentLevelIndex], 32.f, loadtex, "Level_Background", "Data/Audio/Vampire-Killer.wav", audio, enemies);

		Alucard.update(0.f, test, enemies);

		uiManager.restartRequested = false;
		manager.update(Alucard.health, false);
	}

	if (uiManager.nextLevelClicked)
	{
		if (currentLevelIndex + 1 < levels.size())
		{
			currentLevelIndex++;
			Alucard.health = 100;
			Alucard.position = test.load(levels[currentLevelIndex], 32.f, loadtex, "Level_Background", "Data/Audio/Vampire-Killer.wav", audio, enemies);

			Alucard.update(0.f, test, enemies);

			manager.update(Alucard.health, false);
		}
		else
		{
			std::cout << "You beat the final level!" << std::endl;
		}

		uiManager.nextLevelClicked = false;
	}

	bool hitWinTile = test.checkWinCondition(Alucard.box.GetBox());
	manager.update(Alucard.health, hitWinTile);

	if (manager.getState() == GameState::Playing)
	{
		Alucard.update(deltaTime, test, enemies);

		for (auto const& [name, e] : enemies)
		{
			e->move(deltaTime, test);
			if (Alucard.CheckCollision(e->box.GetBox()))
			{
				Alucard.takeDamage(50);
			}
		}

		sf::View mainView;
		mainView.setSize({ 400.f, 300.f });
		mainView.setCenter(Alucard.position);
		this->window->setView(mainView);

		test.draw(*this->window, loadtex);
		loadtex->Draw(*this->window);

		this->window->setView(this->window->getDefaultView());
		playerHUD->update(Alucard.health, 100);
		playerHUD->draw(*this->window);
	}
	else if (manager.getState() == GameState::GameOver)
	{
		this->window->setView(this->window->getDefaultView());
		uiManager.drawDeathScreen(*this->window, deathTex, gameFont);
	}
	else if (manager.getState() == GameState::Win)
	{
		this->window->setView(this->window->getDefaultView());
		uiManager.drawVictoryScreen(*this->window, winTex, gameFont);
	}

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
	loadtex->AddAnimationSet("Background", "Level_Background", AnimationData{ "Backgroundtex", 1, 800, 600 });

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