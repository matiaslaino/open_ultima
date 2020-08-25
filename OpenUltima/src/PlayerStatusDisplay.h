#pragma once
#include "common/LTexture.h"
#include <memory>
#include "Player.h"

using namespace std;

class PlayerStatusDisplay
{
public:
	static constexpr int POSITION_X = 247;
	static constexpr int POSITION_Y = 160;
	static constexpr int WIDTH = 73;
	static constexpr int HEIGHT = 40;

	PlayerStatusDisplay(SDL_Renderer* renderer, shared_ptr<Player> player);
	void update(float elapsed);
	void draw(SDL_Renderer* renderer);
private:
	shared_ptr<Player> _player;

	unique_ptr<LTexture> _textureHits;
	unique_ptr<LTexture> _textureFood;
	unique_ptr<LTexture> _textureXP;
	unique_ptr<LTexture> _textureMoney;
	unique_ptr<LTexture> _background;
};

