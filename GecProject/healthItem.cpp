#include "healthItem.h"

void healthItem::initGraphics(Graphics* graphics)
{
	Character::initGraphics(graphics);
}

void healthItem::onPickup()
{
	isCollected = true;
	position = { -5000.f, -5000.f };
	box.Move(position);

	
	
	texGraphics->RenderSprite(spriteID, position, "IDLE", 0);
	
}