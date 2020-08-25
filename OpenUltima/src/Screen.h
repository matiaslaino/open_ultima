#pragma once
#include <memory>
#include <SDL.h>
#include "GameContext.h"

using namespace std;

class Screen
{
public:
	Screen(shared_ptr<GameContext> gameContext) : _gameContext(gameContext) {}

	virtual void update(float elapsed) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
private:
	shared_ptr<GameContext> _gameContext;
};

