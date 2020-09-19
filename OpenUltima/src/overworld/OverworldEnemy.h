#pragma once

#include <utility>

#include "OverworldTile.h"

class OverworldEnemy {
public:
    OverworldEnemy(int hp, int x, int y, string name, shared_ptr<OverworldTile> tile) :
            _hp(hp), _name(std::move(name)), _tile(std::move(tile)) {
        setCoordinates(x, y);
    }

    string getName() { return _name; };

    int getX() { return _x; }

    int getY() { return _y; }

    void setCoordinates(int x, int y) {
        _x = x;
        _y = y;

        _tile->setCoordinates(x * 16, y * 16);
    }

    void update(float elapsed);
    void draw(SDL_Renderer *renderer, SDL_Rect camera);

private:
    int _x;
    int _y;
    int _hp;
    string _name;
    shared_ptr<OverworldTile> _tile;
};


