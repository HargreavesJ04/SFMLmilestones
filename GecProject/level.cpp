#include "level.h"
#include "Enemy.h"

level::level()
{
}

level::~level()
{
	
}

//I hate this its lazy 
sf::Vector2f level::load(std::string fileName, float tileSize, Graphics* loadtex, std::string bgName, std::string musicName, Audio* audio, std::unordered_map<std::string, Enemy*>& enemyMap, std::vector<healthItem*>& items)
{
	tiles.clear();
	bgtiles.clear();
	enemyMap.clear();
	items.clear();
	bgSpriteName = bgName;

	sf::Vector2f playerStartPos({ 0.f, 0.f });
	int enemyCount = 0;
	int itemCount = 0;

	miniView.setSize({ 800.f, 600.f });
	miniView.setViewport(sf::FloatRect({ 0.75f, 0.f }, { 0.25f, 0.25f }));

	audio->PlayMusic(musicName);

	std::ifstream file(fileName);
	std::string line;
	int row = 0;

	while (std::getline(file, line)) //parses a text file and loops through each tile char by char
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
				loadtex->AddAnimationSet("IDLE", enemyName, AnimationData{ "EIDLEtex", 16 }); //if needed but redudant for this enemy type
				loadtex->AddAnimationSet("WALK", enemyName, AnimationData{ "EWALKtex", 16 });

				Enemy* newEnemy = new Enemy();
				newEnemy->spriteID = enemyName;
				newEnemy->initGraphics(loadtex);
				newEnemy->position = { xPos, yPos - tileSize };

				enemyMap[enemyName] = newEnemy;
				enemyCount++;
			}
			else if (line[col] == 'H')
			{
				std::string itemName = "Health_" + std::to_string(itemCount);

				loadtex->createSprite(itemName);
				loadtex->AddAnimationSet("IDLE", itemName, AnimationData{ "HealthItem", 1 });

				healthItem* newItem = new healthItem();
				newItem->spriteID = itemName;
				newItem->initGraphics(loadtex);
				newItem->position = { xPos, yPos };

				newItem->box.Move(newItem->position);

				items.push_back(newItem);
				itemCount++;
			}

			if (line[col] == '.' || line[col] == ' ' || line[col] == 'P' || line[col] == 'E' || line[col] == 'W' || line[col] == 'H') //adds bg tile to special tiles so its not a back hole
			{
				sf::RectangleShape bgtile({ tileSize, tileSize });
				bgtile.setPosition({ xPos, yPos });
				bgtile.setTexture(&loadtex->getTexture("Tilesetbg"));

				if (line[col] == 'W')
				{
					bgtile.setFillColor(sf::Color(255, 255, 255, 254));
				}

				bgtiles.push_back(bgtile);
			}
		}
		row++;
	}
	return playerStartPos;
}

void level::draw(sf::RenderWindow& window, Graphics* loadtex) // you are not gonna belive what this does
{
	loadtex->RenderSprite("Level_Background", sf::Vector2f(-300.f, 0.f), "Background", 0); //background is loaded first so tileset and other draw textures are in FRONT of it 
	for (auto& bgtile : bgtiles)
	{
		window.draw(bgtile);
	}
	for (auto& tile : tiles)
	{
		window.draw(tile);
	}
}

const std::vector<sf::RectangleShape>& level::getTiles() const //player uses this so it can see WHAT tile they are colliding with
{
	return tiles;
}

bool level::checkWinCondition(sf::FloatRect playerBox)
{
	for (const auto& tile : bgtiles)
	{
		if (tile.getFillColor() == sf::Color(255, 255, 255, 254))
		{
			if (playerBox.findIntersection(tile.getGlobalBounds()))
			{
				return true;
			}
		}
	}

	return false;
}