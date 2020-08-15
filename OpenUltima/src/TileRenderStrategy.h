#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

namespace OpenUltima {
	class TileRenderStrategy
	{
	public:
		virtual void Draw(SDL_Renderer* renderer, SDL_Rect box, vector<uint8_t> bytes) = 0;
	};
}

