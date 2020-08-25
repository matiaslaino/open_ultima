#pragma once
class Player
{
public:
	Player(int initialOverworldX, int initialOverworldY) : _overworldX(initialOverworldX), _overworldY(initialOverworldY) {};
	int getOverworldX() { return _overworldX; };
	int getOverworldY() { return _overworldY; };
	void setOverworldX(int value) { _overworldX = value; };
	void setOverworldY(int value) { _overworldY = value; };
	int getHP() { return _hp; };
	int getFood() { return _food; };
	int getXP() { return _xp; };
	int getMoney() { return _money; };
private:
	int _overworldX;
	int _overworldY;
	int _hp = 150;
	int _food = 200;
	int _xp = 0;
	int _money = 100;
};

