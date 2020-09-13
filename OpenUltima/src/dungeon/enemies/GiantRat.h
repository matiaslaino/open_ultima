#pragma once

#include <SDL2/SDL_render.h>
#include "Enemy.h"

class GiantRat : public Enemy {
public:
    GiantRat(int x, int y) : Enemy(x, y) {}

    void draw(SDL_Renderer *renderer, int distance) override;

    void update(float elapsed) override;

    string getName() override { return "Giant Rat"; };
};


