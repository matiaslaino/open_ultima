#pragma once

#include <vector>
#include <SDL_render.h>
#include <string>
#include <map>

#include "../common/graphics/PixelDecodeStrategy.h"
#include "TownSpriteType.h"

using namespace std;

class TownSpriteTypeLoader {
public:
    void init(const string &tilesFileLocation,
              PixelDecodeStrategy *pixelDecodeStrategy,
              SDL_Renderer *renderer);

    shared_ptr<TownSpriteType> getSpriteType(TownSpriteType::SpriteType type);

private:
    map<TownSpriteType::SpriteType, shared_ptr<TownSpriteType>> _spriteTypeMap;
};