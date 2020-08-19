#pragma once
#include <SDL.h>
#include <memory>
#include "../PixelDecodeStrategy.h"
#include "OverworldSprite.h"

using namespace std;

namespace OpenUltima {
	class Tile
	{
	public:
		Tile(int x, int y, shared_ptr<OverworldSprite> sprite);
		void draw(SDL_Renderer* renderer, SDL_Rect camera);
		void update(float elapsed);

	private:
		static constexpr int TILE_WIDTH = 16;
		static constexpr int TILE_HEIGHT = 16;
		
		shared_ptr<OverworldSprite> _sprite;
		SDL_Rect _box;
		bool isVisible(SDL_Rect camera);

		float _scroll = 0;
		float _swapCounter = 0;
		bool _swapped = false;
	};
}

