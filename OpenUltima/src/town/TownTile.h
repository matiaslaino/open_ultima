#pragma once

#include <SDL.h>
#include <memory>
#include "../common/graphics/PixelDecodeStrategy.h"
#include "TownSpriteType.h"
#include "../common/Tile.h"

using namespace std;

class TownTile : public Tile {
public:
    TownTile(int x, int y, shared_ptr<TownSpriteType> sprite);

    void draw(SDL_Renderer *renderer, SDL_Rect camera) override;

private:
    shared_ptr<TownSpriteType> _sprite;
};