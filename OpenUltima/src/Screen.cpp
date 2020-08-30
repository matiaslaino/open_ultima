#include "Screen.h"

void Screen::clearScreen(SDL_Renderer* renderer)
{
	constexpr SDL_Rect screenRect = { 0, 0, WIDTH, HEIGHT };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &screenRect);
}
