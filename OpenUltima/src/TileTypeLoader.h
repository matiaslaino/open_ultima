#pragma once
#include <string>
#include "PixelDecodeStrategy.h"
#include "overworld/OverworldSprite.h"
#include "common/LTexture.h"

using namespace std;

class TileTypeLoader
{
public:
	vector<shared_ptr<OverworldSprite>> loadOverworldSprites(string tilesFileLocation, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer);
private:
	shared_ptr<LTexture> loadTexture(SDL_RWops* file, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer, int spriteCount, int spriteWidth, int spriteHeight);
};