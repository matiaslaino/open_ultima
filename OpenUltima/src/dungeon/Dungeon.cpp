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

    levelColumns = {
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
            {DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
            {DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
    };
    _levels.push_back(levelColumns);

    _enemiesPerLevel.push_back({make_shared<GiantRat>(2, 3)});
    _laddersPerLevel.push_back({LadderInfo(0, 0, 0, 3, false)});
    _laddersPerLevel.push_back({LadderInfo(0, 3, 0, 0, true)});

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

    // See if there is a ladder where we're standing.
    // I don't like that I'm doing this check again later for other tiles.
    for (const auto &ladder : _laddersPerLevel[level]) {
        if (ladder.fromX == x && ladder.fromY == y) {
            dungeonSpace.ladder = make_shared<LadderInfo>(ladder);
        }
    }

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

        if (level < _enemiesPerLevel.size()) {
            for (const auto &enemy : _enemiesPerLevel[level]) {
                if (enemy->getX() == visibleTileX && enemy->getY() == visibleTileY && !enemy->isDead()) {
                    dungeonSpace.enemy = enemy;
                    break;
                }
            }
        }

        if (level < _laddersPerLevel.size()) {
            for (const auto &ladder : _laddersPerLevel[level]) {
                if (ladder.fromX == visibleTileX && ladder.fromY == visibleTileY) {
                    dungeonSpace.ladder = make_shared<LadderInfo>(ladder);
                    break;
                }
            }
        }

        visibleSpaces.push_back(dungeonSpace);
        i++;
    }

    return visibleSpaces;
}
