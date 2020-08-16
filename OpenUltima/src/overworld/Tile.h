#pragma once
#include <SDL.h>
#include <memory>
#include "../TileRenderStrategy.h"

using namespace std;

namespace OpenUltima {
	class Tile
	{
	public:
		Tile(int x, int y, const shared_ptr<TileType>& tileType);
		void Draw(SDL_Renderer* renderer, SDL_Rect camera);

	private:
		static constexpr int TILE_WIDTH = 16;
		static constexpr int TILE_HEIGHT = 16;
		
		SDL_Rect _box;
		shared_ptr<TileType> _type;
		shared_ptr<TileRenderStrategy> _renderStrategy;
		bool IsVisible(SDL_Rect camera);
	};
}

