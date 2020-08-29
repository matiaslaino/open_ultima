#pragma once
#include <string>
#include <vector>
#include "../CardinalPoint.h"
#include "VisibleDungeonSpace.h"
#include "DungeonFeature.h"

using namespace std;

class Dungeon
{
public:
	Dungeon(string name) : _name(name) {}
	void randomize();
	vector<VisibleDungeonSpace> getVisible(int level, int x, int y, CardinalPoint viewDirection);
private:
	static constexpr int SIZE = 9;
	static constexpr int WALLS = 4;
	static constexpr int MAX_LEVEL = 10;
	static constexpr int MAX_VISIBILITY = 5;

	string _name;
	// level -> column -> cell (9 cells) 
	vector<vector<vector<DungeonFeature>>> _levels;
};

