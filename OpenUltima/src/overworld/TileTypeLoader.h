#pragma once

#include <string>
#include "../common/graphics/PixelDecodeStrategy.h"
#include "OverworldSpriteType.h"
#include "../common/graphics/LTexture.h"

using namespace std;

class TileTypeLoader {
public:
    static vector<shared_ptr<OverworldSpriteType>>
    loadOverworldSprites(const string &tilesFileLocation, PixelDecodeStrategy *pixelDecodeStrategy,
                         SDL_Renderer *renderer);
};