#include "TownManager.h"

void TownManager::init(const shared_ptr<TownSpriteTypeLoader>& spriteTypeLoader, const string& mapFilePath) {
    // Tile definition file contains 51 different tiles, no animations.
    auto file = SDL_RWFromFile(mapFilePath.c_str(), "r+b");

    auto buffer = new uint8_t[MAP_FILE_SIZE * MAPS_COUNT];
    SDL_RWread(file, buffer, MAP_FILE_SIZE, MAPS_COUNT);
    SDL_RWclose(file);

    int townIndex = 0;
    int offset = MAP_FILE_SIZE;
    for (int i = 0; i < MAPS_COUNT; ++i) {
        int x = 0;
        int y = 0;

        auto townPtr = buffer + offset * i;

        vector<shared_ptr<TownTile>> tiles;
        for (int j = 0; j < MAP_FILE_SIZE; ++j) {
            auto spriteType = getTypeFromIndex(townPtr[j]);
            auto sprite = spriteTypeLoader->getSpriteType(spriteType);

            auto tile = make_shared<TownTile>(x * TownSpriteType::SPRITE_SIZE, y * TownSpriteType::SPRITE_SIZE, sprite);
            tiles.push_back(tile);
            // tiles are store top to botton, left to right
            y++;
            if (y == 18) {
                y = 0;
                x++;
            }
        }

        auto town = make_shared<Town>(townIndex++, tiles);
        _towns.push_back(town);
    }

    delete[] buffer;
}

TownSpriteType::SpriteType TownManager::getTypeFromIndex(int index) {
    switch (index) {
        case 0x00:
            return TownSpriteType::SpriteType::SOLID_WALL;
        case 0x01:
            return TownSpriteType::SpriteType::FLOOR;
        case 0x02:
            return TownSpriteType::SpriteType::WATER;
        case 0x03:
            return TownSpriteType::SpriteType::WATER_TOP_LEFT;
        case 0x04:
            return TownSpriteType::SpriteType::WATER_BOTTOM_LEFT;
        case 0x05:
            return TownSpriteType::SpriteType::WATER_TOP_RIGHT;
        case 0x06:
            return TownSpriteType::SpriteType::WATER_BOTTOM_RIGHT;
        case 0x07:
            return TownSpriteType::SpriteType::WATER_DIAGONAL_BOTTOM_RIGHT;
        case 0x08:
            return TownSpriteType::SpriteType::WATER_DIAGONAL_BOTTOM_LEFT;
        case 0x09:
            return TownSpriteType::SpriteType::TREE_SMALL;
        case 0x0A:
            return TownSpriteType::SpriteType::TREE_BIG;
        case 0x0B:
            return TownSpriteType::SpriteType::COUNTER_LEFT_RIGHT;
        case 0x0C:
            return TownSpriteType::SpriteType::COUNTER_TOP_BOTTOM;
        case 0x0D:
            return TownSpriteType::SpriteType::COUNTER_TOP;
        case 0x0E:
            return TownSpriteType::SpriteType::COUNTER_BOTTOM;
        case 0x0F:
            return TownSpriteType::SpriteType::COUNTER_LEFT;
        case 0x10:
            return TownSpriteType::SpriteType::COUNTER_RIGHT;
        case 0x11:
            return TownSpriteType::SpriteType::PERSON_GUARD;
        case 0x12:
            return TownSpriteType::SpriteType::PERSON_PLAYER;
        case 0x13:
            return TownSpriteType::SpriteType::PERSON_JESTER_1;
        case 0x14:
            return TownSpriteType::SpriteType::PERSON_KING;
        case 0x15:
            return TownSpriteType::SpriteType::PERSON_MERCHANT;
        case 0x16:
            return TownSpriteType::SpriteType::PERSON_PRISONER;
        case 0x17:
            return TownSpriteType::SpriteType::BRICK_WALL;
        case 0x18:
            return TownSpriteType::SpriteType::A;
        case 0x19:
            return TownSpriteType::SpriteType::B;
        case 0x1A:
            return TownSpriteType::SpriteType::C;
        case 0x1B:
            return TownSpriteType::SpriteType::D;
        case 0x1C:
            return TownSpriteType::SpriteType::E;
        case 0x1D:
            return TownSpriteType::SpriteType::F;
        case 0x1E:
            return TownSpriteType::SpriteType::G;
        case 0x1F:
            return TownSpriteType::SpriteType::H;
        case 0x20:
            return TownSpriteType::SpriteType::I;
        case 0x21:
            return TownSpriteType::SpriteType::J;
        case 0x22:
            return TownSpriteType::SpriteType::K;
        case 0x23:
            return TownSpriteType::SpriteType::L;
        case 0x24:
            return TownSpriteType::SpriteType::M;
        case 0x25:
            return TownSpriteType::SpriteType::N;
        case 0x26:
            return TownSpriteType::SpriteType::O;
        case 0x27:
            return TownSpriteType::SpriteType::P;
        case 0x28:
            return TownSpriteType::SpriteType::Q;
        case 0x29:
            return TownSpriteType::SpriteType::R;
        case 0x2A:
            return TownSpriteType::SpriteType::S;
        case 0x2B:
            return TownSpriteType::SpriteType::T;
        case 0x2C:
            return TownSpriteType::SpriteType::U;
        case 0x2D:
            return TownSpriteType::SpriteType::V;
        case 0x2E:
            return TownSpriteType::SpriteType::W;
        case 0x2F:
            return TownSpriteType::SpriteType::X;
        case 0x30:
            return TownSpriteType::SpriteType::Y;
        case 0x31:
            return TownSpriteType::SpriteType::Z;
        default:
            return TownSpriteType::SpriteType::NONE;
    }
}
