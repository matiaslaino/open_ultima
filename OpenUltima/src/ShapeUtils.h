#pragma once
#include "common/LTexture.h"
#include <memory>

using namespace std;

class ShapeUtils
{
public:
	enum class Direction { Left, Right };

	static shared_ptr<LTexture> arrow(SDL_Renderer* renderer, Direction direction);
};

