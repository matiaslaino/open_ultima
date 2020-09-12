#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "TownTile.h"

using namespace std;

class Town {
public:
    static constexpr int WIDTH = 38;
    static constexpr int HEIGHT = 18;

    Town(int index, vector<shared_ptr<TownTile>> tiles, bool isCastle) : _index(index),
                                                                         _tiles(std::move(tiles)),
                                                                         _isCastle(isCastle) {}

    vector<shared_ptr<TownTile>> getTiles() { return _tiles; }

    shared_ptr<TownTile> getTile(int x, int y);

    bool isCastle() { return _isCastle; }

private:
    vector<shared_ptr<TownTile>> _tiles;

    int _index;
    bool _isCastle;
};