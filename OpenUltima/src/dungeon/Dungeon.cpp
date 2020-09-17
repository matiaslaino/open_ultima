#include "Dungeon.h"
#include "DungeonFeature.h"
#include "enemies/Thief.h"
#include "enemies/GiantRat.h"

void Dungeon::randomize() {
    vector<vector<DungeonFeature>> levelColumns = {
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
    };
    _levels.push_back(levelColumns);

    /*for (int level = 0; level < MAX_LEVEL; level++) {

    }*/
    _enemiesPerLevel.push_back({make_shared<GiantRat>(2, 3)});
}

DungeonFeature Dungeon::lookLeftFromEast(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return y == 0 ? DungeonFeature::Wall : levelFeatures[x][y - 1];
}

DungeonFeature Dungeon::lookRightFromEast(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return y == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x][y + 1];
}

DungeonFeature Dungeon::lookLeftFromWest(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return y == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x][y + 1];
}

DungeonFeature Dungeon::lookRightFromWest(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return y == 0 ? DungeonFeature::Wall : levelFeatures[x][y - 1];
}

DungeonFeature Dungeon::lookLeftFromNorth(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return x == 0 ? DungeonFeature::Wall : levelFeatures[x - 1][y];
}

DungeonFeature Dungeon::lookRightFromNorth(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return x == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x + 1][y];
}

DungeonFeature Dungeon::lookLeftFromSouth(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return x == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x + 1][y];
}

DungeonFeature Dungeon::lookRightFromSouth(vector<vector<DungeonFeature>> levelFeatures, int x, int y) {
    return x == 0 ? DungeonFeature::Wall : levelFeatures[x - 1][y];
}

DungeonFeature Dungeon::lookLeft(vector<vector<DungeonFeature>> levelFeatures, int x, int y, CardinalPoint point) {
    switch (point) {
        case CardinalPoint::East:
            return lookLeftFromEast(levelFeatures, x, y);
        case CardinalPoint::West:
            return lookLeftFromWest(levelFeatures, x, y);
        case CardinalPoint::North:
            return lookLeftFromNorth(levelFeatures, x, y);
        case CardinalPoint::South:
            return lookLeftFromSouth(levelFeatures, x, y);
    }
}

DungeonFeature Dungeon::lookRight(vector<vector<DungeonFeature>> levelFeatures, int x, int y, CardinalPoint point) {
    switch (point) {
        case CardinalPoint::East:
            return lookRightFromEast(levelFeatures, x, y);
        case CardinalPoint::West:
            return lookRightFromWest(levelFeatures, x, y);
        case CardinalPoint::North:
            return lookRightFromNorth(levelFeatures, x, y);
        case CardinalPoint::South:
            return lookRightFromSouth(levelFeatures, x, y);
    }
}

vector<VisibleDungeonSpace> Dungeon::getVisible(int level, int x, int y, CardinalPoint viewDirection) {
    auto levelFeatures = _levels[level];
    vector<VisibleDungeonSpace> visibleSpaces;
    int i = 1;
    bool wall = false;

    // Get the space we're in
    auto dungeonSpace = VisibleDungeonSpace(levelFeatures[x][y],
                                            lookLeft(levelFeatures, x, y, viewDirection),
                                            lookRight(levelFeatures, x, y, viewDirection));
    visibleSpaces.push_back(dungeonSpace);

    while (i < MAX_VISIBILITY && !wall) {
        int visibleTileX;
        int visibleTileY;
        bool outOfBounds = false;
        switch (viewDirection) {
            case CardinalPoint::East: {
                visibleTileX = x + i;
                visibleTileY = y;

                outOfBounds = visibleTileX == SIZE;
            }
                break;
            case CardinalPoint::West: {
                visibleTileX = x - i;
                visibleTileY = y;

                outOfBounds = visibleTileX == -1;
            }
                break;
            case CardinalPoint::North: {
                visibleTileX = x;
                visibleTileY = y - i;

                outOfBounds = visibleTileY == -1;
            }
                break;
            case CardinalPoint::South: {
                visibleTileX = x;
                visibleTileY = y + i;

                outOfBounds = visibleTileY == SIZE;
            }
                break;
        }

        auto cellFeature = outOfBounds ? DungeonFeature::Wall : levelFeatures[visibleTileX][visibleTileY];
        if (isWalledFeature(cellFeature)) wall = true;

        auto leftFeature = wall ? DungeonFeature::Wall : lookLeft(levelFeatures, visibleTileX, visibleTileY,
                                                                  viewDirection);
        auto rightFeature = wall ? DungeonFeature::Wall : lookRight(levelFeatures, visibleTileX, visibleTileY,
                                                                    viewDirection);
        dungeonSpace = VisibleDungeonSpace(cellFeature,
                                           leftFeature,
                                           rightFeature);

        bool foundNpc = false;
        int npcIndex = 0;
        while (!foundNpc && npcIndex < _enemiesPerLevel[level].size()) {
            auto enemy = _enemiesPerLevel[level][npcIndex++];
            if (enemy->getX() == visibleTileX && enemy->getY() == visibleTileY && !enemy->isDead()) {
                dungeonSpace.enemy = enemy;
            }
        }

        visibleSpaces.push_back(dungeonSpace);
        i++;
    }

    return visibleSpaces;
}
