#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
class Fonts
{
public:
	static void init(SDL_Renderer* renderer);
	static TTF_Font* standard() { return _standard; };
private:
	static TTF_Font* _standard;
};

