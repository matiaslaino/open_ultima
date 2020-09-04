#pragma once

#include <vector>
#include <SDL_render.h>
#include <memory>
#include <string>

#include "PixelDecodeStrategy.h"
#include "LTexture.h"

using namespace std;

class SpriteSheetLoader {
public:
    static shared_ptr<LTexture> loadTexture(SDL_RWops* file, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer, int spriteCount, int spriteWidth, int spriteHeight);
};