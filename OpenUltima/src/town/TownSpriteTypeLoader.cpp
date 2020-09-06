#include "TownSpriteTypeLoader.h"
#include "../common/graphics/SpriteSheetLoader.h"

void TownSpriteTypeLoader::init(const string &tilesFileLocation, PixelDecodeStrategy *pixelDecodeStrategy,
                                SDL_Renderer *renderer) {
    // Tile definition file contains 51 different tiles, no animations.
    auto file = SDL_RWFromFile(tilesFileLocation.c_str(), "r+b");

    auto spriteSheet = SpriteSheetLoader::loadTexture(file, pixelDecodeStrategy, renderer, TownSpriteType::SPRITE_COUNT,
                                                      TownSpriteType::SPRITE_SIZE, TownSpriteType::SPRITE_SIZE);

    SDL_RWclose(file);

    vector<shared_ptr<TownSpriteType>> result;

    auto spriteTypeOrdering = {
            TownSpriteType::SpriteType::SOLID_WALL,
            TownSpriteType::SpriteType::FLOOR,
            TownSpriteType::SpriteType::WATER,
            TownSpriteType::SpriteType::WATER_TOP_LEFT,
            TownSpriteType::SpriteType::WATER_BOTTOM_LEFT,
            TownSpriteType::SpriteType::WATER_TOP_RIGHT,
            TownSpriteType::SpriteType::WATER_BOTTOM_RIGHT,
            TownSpriteType::SpriteType::WATER_DIAGONAL_BOTTOM_RIGHT,
            TownSpriteType::SpriteType::WATER_DIAGONAL_BOTTOM_LEFT,
            TownSpriteType::SpriteType::TREE_SMALL,
            TownSpriteType::SpriteType::TREE_BIG,
            TownSpriteType::SpriteType::COUNTER_LEFT_RIGHT,
            TownSpriteType::SpriteType::COUNTER_TOP_BOTTOM,
            TownSpriteType::SpriteType::COUNTER_TOP,
            TownSpriteType::SpriteType::COUNTER_BOTTOM,
            TownSpriteType::SpriteType::COUNTER_LEFT,
            TownSpriteType::SpriteType::COUNTER_RIGHT,
            TownSpriteType::SpriteType::PERSON_GUARD,
            TownSpriteType::SpriteType::PERSON_PLAYER,
            TownSpriteType::SpriteType::PERSON_JESTER_1,
            TownSpriteType::SpriteType::PERSON_KING,
            TownSpriteType::SpriteType::PERSON_MERCHANT,
            TownSpriteType::SpriteType::PERSON_PRISONER,
            TownSpriteType::SpriteType::BRICK_WALL,
            TownSpriteType::SpriteType::A,
            TownSpriteType::SpriteType::B,
            TownSpriteType::SpriteType::C,
            TownSpriteType::SpriteType::D,
            TownSpriteType::SpriteType::E,
            TownSpriteType::SpriteType::F,
            TownSpriteType::SpriteType::G,
            TownSpriteType::SpriteType::H,
            TownSpriteType::SpriteType::I,
            TownSpriteType::SpriteType::J,
            TownSpriteType::SpriteType::K,
            TownSpriteType::SpriteType::L,
            TownSpriteType::SpriteType::M,
            TownSpriteType::SpriteType::N,
            TownSpriteType::SpriteType::O,
            TownSpriteType::SpriteType::P,
            TownSpriteType::SpriteType::Q,
            TownSpriteType::SpriteType::R,
            TownSpriteType::SpriteType::S,
            TownSpriteType::SpriteType::T,
            TownSpriteType::SpriteType::U,
            TownSpriteType::SpriteType::V,
            TownSpriteType::SpriteType::W,
            TownSpriteType::SpriteType::X,
            TownSpriteType::SpriteType::Y,
            TownSpriteType::SpriteType::Z,
            TownSpriteType::SpriteType::PERSON_JESTER_2,
            TownSpriteType::SpriteType::NONE
    };

    _spriteTypeMap.clear();

    constexpr int spriteOffset = TownSpriteType::SPRITE_SIZE;
    int currentOffset = 0;
    for (auto spriteType: spriteTypeOrdering) {
        auto sprite = make_shared<TownSpriteType>(spriteType, spriteSheet, currentOffset);

        _spriteTypeMap.insert(pair<TownSpriteType::SpriteType, shared_ptr<TownSpriteType>>
                                      (spriteType, sprite));

        currentOffset += spriteOffset;
    }
}

shared_ptr<TownSpriteType> TownSpriteTypeLoader::getSpriteType(TownSpriteType::SpriteType type) {
    return _spriteTypeMap.find(type)->second;
}
