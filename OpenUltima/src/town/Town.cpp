#include "Town.h"

shared_ptr<TownTile> Town::getTile(int x, int y) {
    return _tiles[y + x * HEIGHT];
}
