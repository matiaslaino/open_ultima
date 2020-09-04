#pragma once

#include <vector>
#include <SDL_render.h>
#include "../common/graphics/PixelDecodeStrategy.h"
#include <string>
#include "TownSpriteType.h"

using namespace std;

class TownSpriteTypeLoader {
    vector<shared_ptr<TownSpriteType>>
    loadSpriteTypes(string tilesFileLocation, PixelDecodeStrategy *pixelDecodeStrategy, SDL_Renderer *renderer);
};