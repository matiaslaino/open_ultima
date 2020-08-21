#pragma once
#include <SDL.h>
#include <memory>
#include "../PixelDecodeStrategy.h"
#include "OverworldSpriteType.h"

using namespace std;

namespace OpenUltima {
	class Tile
	{
	public:
		Tile(int x, int y, shared_ptr<OverworldSpriteType> sprite);
		void draw(SDL_Renderer* renderer, SDL_Rect camera);
		void update(float elapsed);

	private:
		static constexpr int TILE_WIDTH = 16;
		static constexpr int TILE_HEIGHT = 16;
		
		shared_ptr<OverworldSpriteType> _sprite;
		SDL_Rect _box;
		bool isVisible(SDL_Rect camera);
	};
}

