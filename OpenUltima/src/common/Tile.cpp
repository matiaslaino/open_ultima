#include "Tile.h"

bool Tile::isVisible(SDL_Rect camera) const {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = _box.x;
    rightA = _box.x + _box.w;
    topA = _box.y;
    bottomA = _box.y + _box.h;

    //Calculate the sides of rect B
    leftB = camera.x;
    rightB = camera.x + camera.w;
    topB = camera.y;
    bottomB = camera.y + camera.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}