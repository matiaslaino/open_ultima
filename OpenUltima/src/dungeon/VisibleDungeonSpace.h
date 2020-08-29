#pragma once

#include <memory>
#include "DungeonFeature.h"

using namespace std;

struct VisibleDungeonSpace {
public:
	VisibleDungeonSpace(DungeonFeature feature_, shared_ptr<VisibleDungeonSpace> left_, shared_ptr<VisibleDungeonSpace> right_) : feature(feature_), left(left_), right(right_) {}

	DungeonFeature feature;
	shared_ptr<VisibleDungeonSpace> left;
	shared_ptr<VisibleDungeonSpace> right;
};