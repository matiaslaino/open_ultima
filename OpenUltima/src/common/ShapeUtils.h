#pragma once
#include "graphics/LTexture.h"
#include <memory>

using namespace std;

class ShapeUtils
{
public:
	enum class Direction { Left, Right };

	static shared_ptr<LTexture> arrow(SDL_Renderer* renderer, Direction direction);
	static void drawFullBorders(SDL_Renderer* renderer);
	static void drawRoundedCorners(SDL_Renderer* renderer);
	static void drawDungeonBorders(SDL_Renderer* renderer);
};

