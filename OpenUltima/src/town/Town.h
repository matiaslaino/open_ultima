#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "TownTile.h"

using namespace std;

class Town {
public:
    Town(int index, vector<shared_ptr<TownTile>> tiles) : _index(index), _tiles(std::move(tiles)) {}

    vector<shared_ptr<TownTile>> getTiles() { return _tiles; }

private:
    vector<shared_ptr<TownTile>> _tiles;
    int _index;
};