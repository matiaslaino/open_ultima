#pragma once

enum class DungeonFeature { None, Wall, HiddenDoor, LadderDown, LadderUp, Door };

static bool isWalledFeature(DungeonFeature feature) {
	return feature == DungeonFeature::Wall || feature == DungeonFeature::Door || feature == DungeonFeature::HiddenDoor;
}