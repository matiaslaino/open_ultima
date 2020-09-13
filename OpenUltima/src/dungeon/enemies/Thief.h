#pragma once

#include <SDL2/SDL_render.h>
#include "Enemy.h"

class Thief : public Enemy {
public:
    Thief(int x, int y) : Enemy(x, y) {}

    void draw(SDL_Renderer *renderer, int distance) override;

    void update(float elapsed) override;

    string getName() override { return "Thief"; };
};


