#include "DungeonScreen.h"

void DungeonScreen::update(float elapsed)
{
}

void DungeonScreen::draw(SDL_Renderer* renderer)
{
	const SDL_Rect screenRect = { 0, 0, WIDTH, HEIGHT };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &screenRect);

	// draw walls
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	// draw opposite wall

	if (_vision.size() == 2) {
		SDL_Rect oppositeWallRect = { 80, 36, 144, 72 };

		SDL_RenderDrawLine(renderer, oppositeWallRect.x, oppositeWallRect.y, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y);
		SDL_RenderDrawLine(renderer, oppositeWallRect.x, oppositeWallRect.y + oppositeWallRect.h - 1, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y + oppositeWallRect.h - 1);

		if (_vision[0].left->feature != DungeonFeature::None) {
			SDL_RenderDrawLine(renderer, UPPER_LEFT_X, UPPER_LEFT_Y, oppositeWallRect.x, oppositeWallRect.y);
			SDL_RenderDrawLine(renderer, oppositeWallRect.x, oppositeWallRect.y, oppositeWallRect.x, oppositeWallRect.y + oppositeWallRect.h - 1);
			SDL_RenderDrawLine(renderer, LOWER_LEFT_X, LOWER_LEFT_Y, oppositeWallRect.x, oppositeWallRect.y + oppositeWallRect.h - 1);
		}
		else {
			SDL_RenderDrawLine(renderer, oppositeWallRect.x, oppositeWallRect.y, 8, oppositeWallRect.y);
			SDL_RenderDrawLine(renderer, oppositeWallRect.x, oppositeWallRect.y + oppositeWallRect.h - 1, 8, oppositeWallRect.y + oppositeWallRect.h - 1);
		}

		if (_vision[0].right->feature != DungeonFeature::None) {
			SDL_RenderDrawLine(renderer, UPPER_RIGHT_X, UPPER_RIGHT_Y, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y);
			SDL_RenderDrawLine(renderer, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y + oppositeWallRect.h - 1);
			SDL_RenderDrawLine(renderer, LOWER_RIGHT_X, LOWER_RIGHT_Y, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y + oppositeWallRect.h - 1);
		}
		else {
			SDL_RenderDrawLine(renderer, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y, WIDTH - 8, oppositeWallRect.y);
			SDL_RenderDrawLine(renderer, oppositeWallRect.x + oppositeWallRect.w - 1, oppositeWallRect.y + oppositeWallRect.h - 1, WIDTH - 8, oppositeWallRect.y + oppositeWallRect.h - 1);
		}
	}
	else {
		drawLeftWalls(renderer);
		drawRightWalls(renderer);
		SDL_RenderDrawLine(renderer, 149, 72, 155, 72);
		SDL_RenderDrawLine(renderer, 149, 73, 155, 73);

		if (_vision.size() == 5) {
			drawLeftWalls(renderer);
			drawRightWalls(renderer);

			SDL_Rect oppositeWallRect = { 143, 68, 18, 8 };

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &oppositeWallRect);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderDrawRect(renderer, &oppositeWallRect);
		}
		else if (_vision.size() == 4) {
			drawLeftWalls(renderer);
			drawRightWalls(renderer);

			SDL_Rect oppositeWallRect = { 134, 63, 36, 18 };

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &oppositeWallRect);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderDrawRect(renderer, &oppositeWallRect);
		}
		else if (_vision.size() == 3) {
			drawLeftWalls(renderer);
			drawRightWalls(renderer);

			SDL_Rect oppositeWallRect = { 116, 54, 72, 36 };

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &oppositeWallRect);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderDrawRect(renderer, &oppositeWallRect);
		}
	}
}

void DungeonScreen::handle(const SDL_Event& e)
{
	auto player = _gameContext->getPlayer();

	if (e.type == SDL_KEYDOWN)
	{
		auto pressedKey = e.key.keysym.sym;

		switch (pressedKey)
		{
		case SDLK_UP: moveForward(); break;
		case SDLK_DOWN: player->dungeonTurn(Direction::Right); player->dungeonTurn(Direction::Right); break;
		case SDLK_LEFT: player->dungeonTurn(Direction::Left); break;
		case SDLK_RIGHT: player->dungeonTurn(Direction::Right); break;
		}

		_vision = _dungeon->getVisible(player->getDungeonLevel(), player->getDungeonX(), player->getDungeonY(), player->getDungeonOrientation());
	}
}

void DungeonScreen::moveForward()
{
	auto player = _gameContext->getPlayer();
	if (_vision[1].feature == DungeonFeature::Wall) return;

	player->dungeonMoveForward();
}

void DungeonScreen::drawLeftWalls(SDL_Renderer* renderer)
{
	SDL_RenderDrawLine(renderer, 8, 0, 149, 72);
	SDL_RenderDrawLine(renderer, 8, 144, 149, 73);
}

void DungeonScreen::drawRightWalls(SDL_Renderer* renderer)
{
	SDL_RenderDrawLine(renderer, 296, 0, 155, 72);
	SDL_RenderDrawLine(renderer, 296, 144, 155, 73);
}
