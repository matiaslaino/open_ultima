#pragma once
#include <memory>
#include "Player.h"
#include "ScreenType.h"

using namespace std;

class GameContext
{
public:
	GameContext(shared_ptr<Player> player) : _player(player) {}

	void enterDungeon();
	ScreenType getCurrentScreen() { return _currentScreen; }
	shared_ptr<Player> getPlayer() { return _player; }
private:
	ScreenType _currentScreen = ScreenType::Overworld;
	shared_ptr<Player> _player;
};

