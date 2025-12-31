#include "level.h"
#include "Enemy.h"

level::level()
{
}

level::~level()
{
	if (miniMapFrame != nullptr)
	{
		delete miniMapFrame;
	}
}

sf::Vector2f level::load(std::string fileName, float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio, std::unordered_map<std::string, Enemy*>& enemyMap)
{
	tiles.clear();
	bgtiles.clear();
	enemyMap.clear();
	bgSpriteName = bgName;

	sf::Vector2f playerStartPos({ 0.f, 0.f });
	int enemyCount = 0;

	miniView.setSize({ 800.f, 600.f });
	miniView.setViewport(sf::FloatRect({ 0.75f, 0.f }, { 0.25f, 0.25f }));

	audio->PlayMusic(musicName);

	std::ifstream file(fileName);
	std::string line;
	int row = 0;

	while (std::getline(file, line))
	{
		for (int col = 0; col < (int)line.length(); col++)
		{
			float xPos = (float)col * tileSize;
			float yPos = (float)row * tileSize;

			if (line[col] == '#')
			{
				sf::RectangleShape tile;
				tile.setSize({ tileSize, tileSize });
				tile.setPosition({ xPos, yPos });
				tile.setTexture(&loadtex->getTexture("Tileset"));
				tiles.push_back(tile);
			}
			else if (line[col] == 'P')
			{
				playerStartPos = { xPos, yPos - tileSize };
			}
			else if (line[col] == 'E')
			{
				std::string enemyName = "Enemy_" + std::to_string(enemyCount);

				loadtex->createSprite(enemyName);
				loadtex->AddAnimationSet("IDLE", enemyName, AnimationData{ "EIDLEtex", 5 });
				loadtex->AddAnimationSet("WALK", enemyName, AnimationData{ "EWALKtex", 5 });

				Enemy* newEnemy = new Enemy();
				newEnemy->spriteID = enemyName;
				newEnemy->initGraphics(loadtex);
				newEnemy->position = { xPos, yPos - tileSize };

				enemyMap[enemyName] = newEnemy;
				enemyCount++;
			}

			if (line[col] == '.' || line[col] == ' ' || line[col] == 'P' || line[col] == 'E')
			{
				sf::RectangleShape bgtile({ tileSize, tileSize });
				bgtile.setPosition({ xPos, yPos });
				bgtile.setTexture(&loadtex->getTexture("Tilesetbg"));
				bgtiles.push_back(bgtile);
			}
		}
		row++;
	}
	return playerStartPos;
}

void level::draw(sf::RenderWindow& window, Graphics* loadtex)
{
	loadtex->RenderSprite("Level_Background", sf::Vector2f(-300.f, 0.f), "Background", 0);
	for (auto& bgtile : bgtiles)
	{
		window.draw(bgtile);
	}
	for (auto& tile : tiles)
	{
		window.draw(tile);
	}
}

const std::vector<sf::RectangleShape>& level::getTiles() const
{
	return tiles;
}