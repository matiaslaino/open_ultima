#pragma once

#include <string>
#include <utility>
#include <vector>
#include "../common/CardinalPoint.h"
#include "VisibleDungeonSpace.h"
#include "DungeonFeature.h"
#include "enemies/Enemy.h"

using namespace std;

class Dungeon {
public:
    explicit Dungeon(string name) : _name(std::move(name)) {}

    void randomize();

    vector<VisibleDungeonSpace> getVisible(int level, int x, int y, CardinalPoint viewDirection);

    vector<shared_ptr<Enemy>> getLevelEnemies(int level) { return _enemiesPerLevel[level]; }

private:
    static constexpr int SIZE = 9;
    static constexpr int WALLS = 4;
    static constexpr int MAX_LEVEL = 10;
    static constexpr int MAX_VISIBILITY = 5;

    vector<vector<shared_ptr<Enemy>>> _enemiesPerLevel;

    string _name;
    // level -> column -> cell (9 cells)
    vector<vector<vector<DungeonFeature>>> _levels;

    DungeonFeature lookLeftFromEast(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookRightFromEast(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookLeftFromWest(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookRightFromWest(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookLeftFromNorth(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookRightFromNorth(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookLeftFromSouth(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookRightFromSouth(vector<vector<DungeonFeature>> levelFeatures, int x, int y);

    DungeonFeature lookLeft(vector<vector<DungeonFeature>> levelFeatures, int x, int y, CardinalPoint point);

    DungeonFeature lookRight(vector<vector<DungeonFeature>> levelFeatures, int x, int y, CardinalPoint point);
};

