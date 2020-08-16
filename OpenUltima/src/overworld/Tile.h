#pragma once
#include <SDL.h>
#include <memory>
#include "../TileRenderStrategy.h"

using namespace std;

namespace OpenUltima {
	class Tile
	{
		const int TILE_WIDTH = 16;
		const int TILE_HEIGHT = 16;

	public:
		Tile(int x, int y, const shared_ptr<TileType>& tileType, const shared_ptr<TileRenderStrategy> renderStrategy);
		void Draw(SDL_Renderer* renderer);
		//~Tile();
		void DrawWithTexture(SDL_Renderer* renderer);

	private:
		SDL_Rect _box;
		shared_ptr<TileType> _type;
		shared_ptr<TileRenderStrategy> _renderStrategy;
		SDL_Texture* _texture;
	};
}

