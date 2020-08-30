#include "Dungeon.h"
#include "DungeonFeature.h"

void Dungeon::randomize()
{
	vector<vector<DungeonFeature>> levelColumns = { 
		{DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
		{DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None, DungeonFeature::None},
		{DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Door, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::Door, DungeonFeature::None, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::Door, DungeonFeature::None, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::Door, DungeonFeature::None, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::Door, DungeonFeature::None, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
		{DungeonFeature::Door, DungeonFeature::None, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall, DungeonFeature::Wall},
	};
	_levels.push_back(levelColumns);

	/*for (int level = 0; level < MAX_LEVEL; level++) {

	}*/
}

vector<VisibleDungeonSpace> Dungeon::getVisible(int level, int x, int y, CardinalPoint viewDirection)
{
	auto levelFeatures = _levels[level];
	vector<VisibleDungeonSpace> visibleSpaces;
	int i = 0;
	bool wall = false;

	switch (viewDirection) {
	case CardinalPoint::East:
		while (i < MAX_VISIBILITY && !wall) {
			auto cellIndex = x + i;

			auto cellFeature = cellIndex == SIZE ? DungeonFeature::Wall : levelFeatures[cellIndex][y];
			if (isWalledFeature(cellFeature)) wall = true;

			auto leftFeature = wall || y == 0 ? DungeonFeature::Wall : levelFeatures[cellIndex][y - 1];
			auto rightFeature = wall || y == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[cellIndex][y + 1];
			auto dungeonSpace = VisibleDungeonSpace(cellFeature, make_shared<VisibleDungeonSpace>(leftFeature, nullptr, nullptr), make_shared<VisibleDungeonSpace>(rightFeature, nullptr, nullptr));

			visibleSpaces.push_back(dungeonSpace);
			i++;
		}
		break;
	case CardinalPoint::West: {
		while (i < MAX_VISIBILITY && !wall) {
			auto cellIndex = x - i;
			auto cellFeature = cellIndex == -1 ? DungeonFeature::Wall : levelFeatures[cellIndex][y];
			if (isWalledFeature(cellFeature)) wall = true;

			auto leftFeature = wall || y == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[cellIndex][y + 1];
			auto rightFeature = wall || y == 0 ? DungeonFeature::Wall : levelFeatures[cellIndex][y - 1];
			auto dungeonSpace = VisibleDungeonSpace(cellFeature, make_shared<VisibleDungeonSpace>(leftFeature, nullptr, nullptr), make_shared<VisibleDungeonSpace>(rightFeature, nullptr, nullptr));

			visibleSpaces.push_back(dungeonSpace);
			i++;
		}
		break;
	}
	case CardinalPoint::North: {
		while (i < MAX_VISIBILITY && !wall) {
			auto cellIndex = y - i;
			auto cellFeature = cellIndex == -1 ? DungeonFeature::Wall : levelFeatures[x][cellIndex];
			if (isWalledFeature(cellFeature)) wall = true;

			auto leftFeature = wall || x == 0 ? DungeonFeature::Wall : levelFeatures[x - 1][cellIndex];
			auto rightFeature = wall || x == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x + 1][cellIndex];
			auto dungeonSpace = VisibleDungeonSpace(cellFeature, make_shared<VisibleDungeonSpace>(leftFeature, nullptr, nullptr), make_shared<VisibleDungeonSpace>(rightFeature, nullptr, nullptr));

			visibleSpaces.push_back(dungeonSpace);
			i++;
		}
	} break;
	case CardinalPoint::South:
		while (i < MAX_VISIBILITY && !wall) {
			auto cellIndex = y + i;
			auto cellFeature = cellIndex == SIZE ? DungeonFeature::Wall : levelFeatures[x][cellIndex];
			if (isWalledFeature(cellFeature)) wall = true;

			auto leftFeature = wall || x == SIZE - 1 ? DungeonFeature::Wall : levelFeatures[x + 1][cellIndex];
			auto rightFeature = wall || x == 0 ? DungeonFeature::Wall : levelFeatures[x - 1][cellIndex];
			auto dungeonSpace = VisibleDungeonSpace(cellFeature, make_shared<VisibleDungeonSpace>(leftFeature, nullptr, nullptr), make_shared<VisibleDungeonSpace>(rightFeature, nullptr, nullptr));

			visibleSpaces.push_back(dungeonSpace);
			i++;
		}
		break;
	}

	return visibleSpaces;
}
