#pragma once
class Player
{
public:
	Player(int initialOverworldX, int initialOverworldY) : _overworldX(initialOverworldX), _overworldY(initialOverworldY) {};
	int getOverworldX() { return _overworldX; };
	int getOverworldY() { return _overworldY; };
	void setOverworldX(int value) { _overworldX = value; };
	void setOverworldY(int value) { _overworldY = value; };
private:
	int _overworldX;
	int _overworldY;
};

