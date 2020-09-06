#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "TownTile.h"

using namespace std;

TownTile::TownTile(int x, int y, shared_ptr<TownSpriteType> sprite)
        : _sprite(std::move(sprite)) {
    _box.x = x;
    _box.y = y;

    _box.w = TownSpriteType::SPRITE_SIZE;
    _box.h = TownSpriteType::SPRITE_SIZE;
}

void TownTile::draw(SDL_Renderer *renderer, SDL_Rect camera) {
    if (isVisible(camera)) {
        if (_sprite != nullptr) {
            SDL_Rect adjustedRenderTargetQuad = {_box.x - camera.x, _box.y - camera.y,
                                                 _box.w, _box.h};
            const auto source = _sprite->getSource();
            SDL_RenderCopyEx(renderer, _sprite->getTexture()->getRawTexture(), &source,
                             &adjustedRenderTargetQuad, 0, nullptr, SDL_FLIP_NONE);
        }
    }
}

bool TownTile::isVisible(SDL_Rect camera) const {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = _box.x;
    rightA = _box.x + _box.w;
    topA = _box.y;
    bottomA = _box.y + _box.h;

    //Calculate the sides of rect B
    leftB = camera.x;
    rightB = camera.x + camera.w;
    topB = camera.y;
    bottomB = camera.y + camera.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}