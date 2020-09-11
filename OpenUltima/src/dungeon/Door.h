#pragma once

#include "../common/Direction.h"
#include <SDL.h>

class Door {
public:
    static void draw(SDL_Renderer *renderer, int distance, Direction direction);

    static void drawFrontFacing(SDL_Renderer *renderer, int distance);
};

