#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "TownTile.h"

using namespace std;

TownTile::TownTile(int x, int y, shared_ptr<TownSpriteType> sprite) :
        Tile({x, y, sprite->getSource().w, sprite->getSource().h}),
        _sprite(std::move(sprite)) {}

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