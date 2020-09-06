#include <memory>
#include <utility>
#include "OverworldTile.h"

using namespace std;

OverworldTile::OverworldTile(int x, int y, shared_ptr<OverworldSpriteType> sprite,
                             shared_ptr<TileAnimation> tileAnimation)
        : Tile({x, y, sprite->getSource().w, sprite->getSource().h}), _sprite(std::move(sprite)),
          _tileAnimation(std::move(tileAnimation)) {}

void OverworldTile::draw(SDL_Renderer *renderer, SDL_Rect camera) {
    if (isVisible(camera)) {
        auto renderQuads = _tileAnimation->getRenderQuads(renderer, _sprite->getAnimationType(), _box,
                                                          _sprite->getSource(),
                                                          _sprite->getSwapOffset());

        for (auto renderQuad : renderQuads) {
            SDL_Rect adjustedRenderTargetQuad = {renderQuad.target.x - camera.x, renderQuad.target.y - camera.y,
                                                 renderQuad.target.w, renderQuad.target.h};
            SDL_RenderCopyEx(renderer, _sprite->getTexture()->getRawTexture(), &renderQuad.source,
                             &adjustedRenderTargetQuad, 0, nullptr, SDL_FLIP_NONE);
        }
    }
}

void OverworldTile::update(float elapsed) {
    _tileAnimation->update(elapsed, _sprite->getAnimationType(), _box);
}