#pragma once
#include <SDL.h>
class GameObject
{
	virtual void update(float elapsed) = 0;
	virtual void draw(SDL_Renderer* renderer, SDL_Rect camera) = 0;
};

