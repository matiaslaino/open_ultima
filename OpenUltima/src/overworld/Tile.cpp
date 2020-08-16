#include <cstddef>
#include <memory>

#include "TileType.h"
#include "Tile.h"

using namespace std;
using namespace OpenUltima;

Tile::Tile(int x, int y, const shared_ptr<TileType>& tileType)
{
	_box.x = x;
	_box.y = y;

	_box.w = TILE_WIDTH;
	_box.h = TILE_HEIGHT;

	_type = tileType;
}

void Tile::Draw(SDL_Renderer* renderer, SDL_Rect camera) {
    if (IsVisible(camera)) {
        SDL_Rect renderQuad = { _box.x - camera.x, _box.y - camera.y, _box.w, _box.h };

	    SDL_RenderCopyEx(renderer, _type->GetTexture(), NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
    }
}

bool Tile::IsVisible(SDL_Rect camera)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = _box.x;
    rightA = _box.x + _box.w;
    topA = _box.y;
    bottomA = _box.y + _box.h;

    //Calculate the sides of rect B
    leftB = camera.x;
    rightB = camera.x + camera.w;
    topB = camera.y;
    bottomB = camera.y + camera.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}