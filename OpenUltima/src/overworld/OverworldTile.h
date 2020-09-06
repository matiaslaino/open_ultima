#pragma once

#include <SDL.h>
#include <memory>
#include "../common/graphics/PixelDecodeStrategy.h"
#include "OverworldSpriteType.h"
#include "../common/Tile.h"

using namespace std;

class OverworldTile : public Tile {
public:
    OverworldTile(int x, int y, shared_ptr<OverworldSpriteType> sprite, shared_ptr<TileAnimation> tileAnimation);

    void draw(SDL_Renderer *renderer, SDL_Rect camera) override;
    void update(float elapsed);


private:
    shared_ptr<OverworldSpriteType> _sprite;
    shared_ptr<TileAnimation> _tileAnimation;

};