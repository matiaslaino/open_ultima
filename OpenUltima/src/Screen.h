#pragma once
#include <memory>
#include <SDL.h>
#include "GameContext.h"

using namespace std;

class Screen
{
public:
	static constexpr int WIDTH = 304;
	static constexpr int HEIGHT = 144;

	Screen(shared_ptr<GameContext> gameContext) : _gameContext(gameContext) {}

	virtual void update(float elapsed) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void handle(const SDL_Event& e) {}
protected:
	shared_ptr<GameContext> _gameContext;
	void clearScreen(SDL_Renderer* renderer);
};

