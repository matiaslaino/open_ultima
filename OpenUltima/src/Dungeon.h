#pragma once
#include "Screen.h"

class Dungeon: public Screen
{
public:
	Dungeon(shared_ptr<GameContext> gameContext) : Screen(gameContext) {}

	// Inherited via Screen
	virtual void update(float elapsed) override;
	virtual void draw(SDL_Renderer* renderer) override;
};

