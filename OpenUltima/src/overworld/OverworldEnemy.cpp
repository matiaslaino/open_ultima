#include "OverworldEnemy.h"

void OverworldEnemy::draw(SDL_Renderer *renderer, SDL_Rect camera) {
    _tile->draw(renderer, camera);
}

void OverworldEnemy::update(float elapsed) {
    _tile->update(elapsed);
}
