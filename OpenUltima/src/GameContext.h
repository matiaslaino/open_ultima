#pragma once

#include <memory>
#include <utility>
#include "Player.h"
#include "ScreenType.h"

using namespace std;

class GameContext {
public:
    explicit GameContext(shared_ptr<Player> player) : _player(std::move(player)) {}

    void setScreen(ScreenType screenType) { _currentScreen = screenType; }

    void enterTown() {
        _currentScreen = ScreenType::Town;
        _inCastle = false;
    }

    void enterCastle() {
        _currentScreen = ScreenType::Town;
        _inCastle = true;
    }

    ScreenType getCurrentScreen() { return _currentScreen; }

    shared_ptr<Player> getPlayer() { return _player; }

    bool isInCastle() { return _inCastle; }

private:
    ScreenType _currentScreen = ScreenType::Overworld;
    shared_ptr<Player> _player;
    bool _inCastle = false;
};

