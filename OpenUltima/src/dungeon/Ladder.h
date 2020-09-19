#pragma once

#include <SDL2/SDL_render.h>

class Ladder {
public:
    static void drawFront(SDL_Renderer *renderer, int distance, bool goingUp);

    static void drawFromSide(SDL_Renderer *pRenderer, int distance, bool up);
};


