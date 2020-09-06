#pragma once

#include <memory>

#include "Town.h"
#include "TownSpriteTypeLoader.h"

using namespace std;

class TownManager {
public:
    void init(const shared_ptr<TownSpriteTypeLoader> &spriteTypeLoader, const string &mapFilePath);

    shared_ptr<Town> getTown(int x, int y);

    shared_ptr<Town> getCastle(int x, int y);

private:
    static constexpr int MAPS_COUNT = 10;
    static constexpr int MAP_WIDTH = 38;
    static constexpr int MAP_HEIGHT = 18;
    static constexpr int MAP_FILE_SIZE = 684;

    vector<shared_ptr<Town>> _towns;

    static TownSpriteType::SpriteType getTypeFromIndex(int index);
};