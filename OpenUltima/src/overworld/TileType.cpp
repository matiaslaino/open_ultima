#include "TileType.h"

TileType::TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition)
{
	_definition = definition;
	_height = tileHeight;
	_width = tileWidth;
}

vector<uint8_t> TileType::getDefinition() const
{
	return _definition;
}

int TileType::getHeight() const
{
	return _height;
}

int TileType::getWidth() const
{
	return _width;
}

