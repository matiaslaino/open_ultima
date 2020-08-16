#pragma once
#include <SDL.h>
#include <memory>
#include "../PixelDecodeStrategy.h"

using namespace std;

namespace OpenUltima {
	class Tile
	{
	public:
		Tile(int x, int y, const shared_ptr<TileType>& tileType);
		void Draw(SDL_Renderer* renderer, SDL_Rect camera);
		void Update(float timeElapsed);

	private:
		static constexpr int TILE_WIDTH = 16;
		static constexpr int TILE_HEIGHT = 16;
		
		SDL_Rect _box;
		shared_ptr<TileType> _type;
		shared_ptr<PixelDecodeStrategy> _renderStrategy;
		bool IsVisible(SDL_Rect camera);
		int _currentAnimationFrame = 0;
		float _animationCounter = 0;
	};
}

