#include "TownSpriteTypeLoader.h"
#include "../common/graphics/SpriteSheetLoader.h"

vector<shared_ptr<TownSpriteType>>
TownSpriteTypeLoader::loadSpriteTypes(string tilesFileLocation, PixelDecodeStrategy *pixelDecodeStrategy,
                                      SDL_Renderer *renderer) {
    // Tile definition file contains 52 different tiles, some are actually the animated portion of another tile (castle with flag up, and with flag down).
    SDL_RWops *file = SDL_RWFromFile(tilesFileLocation.c_str(), "r+b");

    auto overworldTexture = SpriteSheetLoader::loadTexture(file, pixelDecodeStrategy, renderer, 52, 16, 16);

    vector<shared_ptr<TownSpriteType>> result;

    return result;
}