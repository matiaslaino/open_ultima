#pragma once

#include <SDL2/SDL_render.h>

class Tile {
public:
    explicit Tile(SDL_Rect box) : _box(box) {};

    virtual void draw(SDL_Renderer *renderer, SDL_Rect camera) = 0;

    void setCoordinates(int x, int y) {
        _box.x = x;
        _box.y = y;
    }

protected:
    SDL_Rect _box;

    [[nodiscard]] bool isVisible(SDL_Rect camera) const;
};


