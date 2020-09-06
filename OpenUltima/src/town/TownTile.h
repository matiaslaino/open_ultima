#pragma once

#include <SDL.h>
#include <memory>
#include "../common/graphics/PixelDecodeStrategy.h"
#include "TownSpriteType.h"

using namespace std;

class TownTile {
public:
    TownTile(int x, int y, shared_ptr<TownSpriteType> sprite);

    void draw(SDL_Renderer *renderer, SDL_Rect camera);

    void setCoordinates(int x, int y) {
        _box.x = x;
        _box.y = y;
    }

private:
    shared_ptr<TownSpriteType> _sprite;
    SDL_Rect _box;

    bool isVisible(SDL_Rect camera) const;
};