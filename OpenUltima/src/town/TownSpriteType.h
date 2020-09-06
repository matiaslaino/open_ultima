#pragma once

#include "../common/graphics/LTexture.h"
#include <memory>
#include <utility>

using namespace std;

class TownSpriteType {
public:
    enum class SpriteType {
        SOLID_WALL, FLOOR, WATER, WATER_TOP_LEFT, WATER_BOTTOM_LEFT, WATER_TOP_RIGHT, WATER_BOTTOM_RIGHT,
        WATER_DIAGONAL_BOTTOM_RIGHT, WATER_DIAGONAL_BOTTOM_LEFT, TREE_SMALL, TREE_BIG, COUNTER_LEFT_RIGHT,
        COUNTER_TOP_BOTTOM, COUNTER_TOP, COUNTER_BOTTOM, COUNTER_LEFT, COUNTER_RIGHT, PERSON_GUARD,
        PERSON_PLAYER, PERSON_JESTER_1, PERSON_KING, PERSON_MERCHANT, PERSON_PRISONER, BRICK_WALL,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, PERSON_JESTER_2, NONE
    };

    static constexpr int SPRITE_COUNT = 51;
    static constexpr int SPRITE_SIZE = 8;

    TownSpriteType(SpriteType type, shared_ptr<LTexture> texture, int textureOffset) {
        _type = type;
        _texture = std::move(texture);
        _source = {textureOffset, 0, SPRITE_SIZE, SPRITE_SIZE};
    }

    shared_ptr<LTexture> getTexture() { return _texture; };

    SDL_Rect getSource() { return _source; }

    SpriteType getType() { return _type; };

private:
    shared_ptr<LTexture> _texture;
    SDL_Rect _source;
    SpriteType _type;
};