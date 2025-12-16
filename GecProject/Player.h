#pragma once
#include "Character.h"
class Player : public Character
{
public: 

	void move();
	void initGraphics(Graphics* texGraphics) override; 
	void initAudio(Audio* audio) override;

private:

	
	std::string setState(Movement state);
};

