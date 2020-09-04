#pragma once

#include "common/CardinalPoint.h"
#include "common/Direction.h"

class Player {
public:
    Player(int initialOverworldX, int initialOverworldY) : _overworldX(initialOverworldX),
                                                           _overworldY(initialOverworldY) {};

    int getOverworldX() const { return _overworldX; };

    int getOverworldY() const { return _overworldY; };

    void setOverworldX(int value) { _overworldX = value; };

    void setOverworldY(int value) { _overworldY = value; };

    int getDungeonX() const { return _dungeonX; };

    int getDungeonY() const { return _dungeonY; };

    void setDungeonX(int value) { _dungeonX = value; };

    void setDungeonY(int value) { _dungeonY = value; };

    int getDungeonLevel() const { return _dungeonLevel; };

    void setDungeonLevel(int value) { _dungeonLevel = value; };

    CardinalPoint getDungeonOrientation() { return _dungeonOrientation; };

    void dungeonTurn(Direction value);

    void dungeonMoveForward();

    int getHP() const { return _hp; };

    int getFood() const { return _food; };

    int getXP() const { return _xp; };

    int getMoney() const { return _money; };
private:
    int _overworldX;
    int _overworldY;
    int _dungeonY = 0;
    int _dungeonX = 2;
    int _dungeonLevel = 0;
    CardinalPoint _dungeonOrientation = CardinalPoint::South;

    int _hp = 150;
    int _food = 200;
    int _xp = 0;
    int _money = 100;
};

