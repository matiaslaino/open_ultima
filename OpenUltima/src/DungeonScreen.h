#pragma once
#include "Screen.h"
#include "dungeon/Dungeon.h"
#include "common/LTexture.h"

class DungeonScreen : public Screen
{
public:
	DungeonScreen(shared_ptr<GameContext> gameContext) : Screen(gameContext) {}

	// Inherited via Screen
	virtual void update(float elapsed) override;
	virtual void draw(SDL_Renderer* renderer) override;
	virtual void handle(const SDL_Event& e) override;

	void setDungeon(shared_ptr<Dungeon> dungeon) { 
		_dungeon = dungeon; 
		auto player = _gameContext->getPlayer();
		_vision = _dungeon->getVisible(player->getDungeonLevel(), player->getDungeonX(), player->getDungeonY(), player->getDungeonOrientation());
	}

private:
	static constexpr int UPPER_LEFT_X = 8;
	static constexpr int UPPER_LEFT_Y = 0;
	static constexpr int UPPER_RIGHT_X = 296;
	static constexpr int UPPER_RIGHT_Y = 0;
	static constexpr int LOWER_LEFT_X = 8;
	static constexpr int LOWER_LEFT_Y = 144;
	static constexpr int LOWER_RIGHT_X = 296;
	static constexpr int LOWER_RIGHT_Y = 144;

	shared_ptr<Dungeon> _dungeon;
	vector<VisibleDungeonSpace> _vision;
	int _drawCounter = 0;
	int _drawEnabled = true;

	void moveForward();
	
	void drawLeftWalls(SDL_Renderer* renderer);
	void drawRightWalls(SDL_Renderer* renderer);
};

