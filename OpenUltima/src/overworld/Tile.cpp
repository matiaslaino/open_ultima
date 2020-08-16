#include <cstddef>
#include <memory>

#include "TileType.h"
#include "Tile.h"

using namespace std;
using namespace OpenUltima;

Tile::Tile(int x, int y, const shared_ptr<TileType>& tileType, const shared_ptr<TileRenderStrategy> renderStrategy)
{
	_box.x = x;
	_box.y = y;

	_box.w = TILE_WIDTH;
	_box.h = TILE_HEIGHT;

	_type = tileType;
	_renderStrategy = renderStrategy;
}

void Tile::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, _type->GetTexture(), NULL, &_box, 0, NULL, SDL_FLIP_NONE);
}

