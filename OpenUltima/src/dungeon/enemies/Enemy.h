#pragma once

#include <SDL2/SDL_render.h>
#include <string>

using namespace std;

class Enemy {
public:
    Enemy(int x, int y) : _x(x), _y(y) {}

    virtual void update(float elapsed) = 0;

    virtual void draw(SDL_Renderer *renderer, int distance) = 0;

    virtual string getName() = 0;

    int getX() { return _x; }

    int getY() { return _y; }

protected:
    int _x;
    int _y;
    int _hp;
};


