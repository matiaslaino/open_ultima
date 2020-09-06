#pragma once

#include <SDL.h>
#include <memory>
#include "../common/graphics/PixelDecodeStrategy.h"
#include "OverworldSpriteType.h"

using namespace std;

namespace OpenUltima {
    class Tile {
    public:
        Tile(int x, int y, shared_ptr<OverworldSpriteType> sprite, shared_ptr<TileAnimation> tileAnimation);

        void draw(SDL_Renderer *renderer, SDL_Rect camera);

        void update(float elapsed);

        void setCoordinates(int x, int y) {
            _box.x = x;
            _box.y = y;
        }

    private:
        static constexpr int TILE_WIDTH = 16;
        static constexpr int TILE_HEIGHT = 16;

        shared_ptr<OverworldSpriteType> _sprite;
        SDL_Rect _box;
        shared_ptr<TileAnimation> _tileAnimation;

        bool isVisible(SDL_Rect camera) const;
    };
}