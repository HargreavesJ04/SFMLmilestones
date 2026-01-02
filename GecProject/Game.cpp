#include "Game.h"
#include <iostream>

Game::Game()
{
	initWindow();
	initGraphics();
	initAudio();

	playerHUD = new HUD();
	playerHUD->initGraphics(loadtex);

	uiManager.initGraphics(loadtex);

	levels.push_back("Data/Levels/Level1.txt");
	levels.push_back("Data/Levels/Level1.txt"); //placeholder for level 2 just here to test level switching

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

		for (auto const& [name, e] : enemies) //collision detection between player and enemies 
		{
			e->move(deltaTime, test);
			if (Alucard.CheckCollision(e->box.GetBox()))
			{
				Alucard.takeDamage(50);
			}
		}

		sf::View mainView; //main camera view thats follows player
		mainView.setSize({ 400.f, 300.f });
		mainView.setCenter(Alucard.position);
		this->window->setView(mainView);

		test.draw(*this->window, loadtex);
		loadtex->Draw(*this->window);

		this->window->setView(this->window->getDefaultView());

		sf::RectangleShape minimapBg;
		minimapBg.setSize({ 160.f, 120.f });
		minimapBg.setPosition({ 600.f, 30.f });
		minimapBg.setFillColor(sf::Color(80, 0, 0, 200));
		minimapBg.setOutlineThickness(2.f);
		minimapBg.setOutlineColor(sf::Color(150, 20, 20));

		this->window->draw(minimapBg);

		sf::View minimapView; //minimap view that also follows player so player can see surroundings
		minimapView.setCenter(Alucard.position);
		minimapView.setSize({ 1600.f, 1200.f });
		minimapView.setViewport(sf::FloatRect({ 0.75f, 0.05f }, { 0.2f, 0.2f }));
		this->window->setView(minimapView);

		test.draw(*this->window, loadtex);
		loadtex->Draw(*this->window);

		this->window->setView(this->window->getDefaultView());
		playerHUD->update(Alucard.health, 100);
		playerHUD->draw(*this->window);
	}
	else if (manager.getState() == GameState::GameOver)
	{
		audio->StopMusic();
		Alucard.stopSound("WALK");
		this->window->setView(this->window->getDefaultView());
		uiManager.drawDeathScreen(*this->window);
	}
	else if (manager.getState() == GameState::Win)
	{
		audio->StopMusic();
		Alucard.stopSound("WALK");
		this->window->setView(this->window->getDefaultView());
		uiManager.drawVictoryScreen(*this->window);
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
	//tiles 
	loadtex->loadTexture("Data/Textures/Tilesets/dirt.png", "Tileset");
	loadtex->loadTexture("Data/Textures/Tilesets/dirt2.png", "Tilesetbg");

	//level background 
	loadtex->loadTexture("Data/Textures/Background/Background.png", "Backgroundtex");
	loadtex->createSprite("Level_Background");
	loadtex->AddAnimationSet("Background", "Level_Background", AnimationData{ "Backgroundtex", 1, 800, 600 });

	//Player Textures
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "IDLEtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "ATTACKtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "WALKtex");
	loadtex->createSprite("Player");

	//Enemy Textures
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EIDLEtex");
	loadtex->loadTexture("Data/Textures/AlucardSprites/ALwalk.png", "EWALKtex");

	//HUD Textures
	loadtex->loadTexture("Data/UI/alucardHpBar.png", "HUDtex");

	// Load UI Textures 
	loadtex->loadTexture("Data/Textures/Background/GameOver.png", "DeathTex");
	loadtex->loadTexture("Data/Textures/Background/WinScreen.png", "WinTex");
}

void Game::initAudio()
{
	audio->SetMusicVolume(15.f);
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }), "GEC Project [Totally NOT Castlevania]");
	this->window->setFramerateLimit(20);
}