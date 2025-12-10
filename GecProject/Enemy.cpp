#include "Enemy.h"
#include <iostream>

void Enemy::initEnemyGraphics()
{
	position = { 400.f, 300.f };
	size = { 60.f, 62.f };

	if (!texGraphics->loadTexture("Data/Textures/MaleZombie/attack_combined.png", "ENEMY_ATTACKtex"))
		std::cout << "Failed to load texture: Enemy Attack (1).png\n";
	if (!texGraphics->loadTexture("Data/Textures/MaleZombie/walk_combined.png", "ENEMY_WALKtex"))
		std::cout << "Failed to load texture: Enemy Walk (1).png\n";

	texGraphics->createSprite("EnemySprite");

	texGraphics->AddAnimationSet("ENEMY_ATTACK", "EnemySprite",
		AnimationData{ "ENEMY_ATTACKtex", 8,  432, 521 });

	texGraphics->RenderSprite("EnemySprite", position, "ENEMY_ATTACK", 0);
}