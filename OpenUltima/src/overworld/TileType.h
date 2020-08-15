#pragma once
#include <cstddef>
#include <vector>
#include <SDL.h>
#include <memory>

using namespace std;

class TileType
{
public:
	TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition);
	vector<uint8_t> getDefinition() const;
	int getHeight() const;
	int getWidth() const;

private:
	vector<uint8_t> _definition;
	int _height;
	int _width;
};

