#pragma once
#include "Character.h"
#include "Graphics.h"



class healthItem : public Character
{
public:
	
	std::string spriteID;
	bool isCollected = false;
	void initGraphics(Graphics* graphics) override;
	void onPickup(); 


private:



};

