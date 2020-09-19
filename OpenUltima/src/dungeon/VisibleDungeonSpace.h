#pragma once

#include <memory>
#include <utility>
#include "DungeonFeature.h"
#include "enemies/Enemy.h"
#include "Ladder.h"
#include "LadderInfo.h"

using namespace std;

struct VisibleDungeonSpace {
public:
    VisibleDungeonSpace(DungeonFeature feature_, DungeonFeature left_,
                        DungeonFeature right_) : feature(feature_), left(left_),
                                                 right(right_) {}

    DungeonFeature feature;
    DungeonFeature left;
    DungeonFeature right;
    shared_ptr<Enemy> enemy = nullptr;
    shared_ptr<LadderInfo> ladder = nullptr;
};