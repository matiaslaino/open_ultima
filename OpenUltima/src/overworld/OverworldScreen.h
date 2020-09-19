#pragma once

#include "../GameObject.h"
#include <utility>
#include <vector>
#include "OverworldTile.h"
#include "OverworldEnemy.h"
#include "OverworldSpriteType.h"
#include "../Player.h"
#include "Constants.h"
#include <functional>
#include "../PlayerStatusDisplay.h"
#include <map>
#include "../GameContext.h"
#include "../Screen.h"

using namespace std;

class OverworldScreen : public Screen {
public:
    static constexpr int DISPLAY_SIZE_TILES_WIDTH = 19;
    static constexpr int DISPLAY_SIZE_TILES_HEIGHT = 9;
    static constexpr int MAP_WIDTH_PX = DISPLAY_SIZE_TILES_WIDTH * TILE_WIDTH;
    static constexpr int MAP_HEIGHT_PX = DISPLAY_SIZE_TILES_HEIGHT * TILE_WIDTH;

    OverworldScreen(shared_ptr<GameContext> context, int widthTiles, int heightTiles) : Screen(std::move(context)) {
        _camera.w = DISPLAY_SIZE_TILES_WIDTH * TILE_WIDTH;
        _camera.h = DISPLAY_SIZE_TILES_HEIGHT * TILE_HEIGHT;

        setCamera();
    };

    void init(SDL_Renderer *renderer, PixelDecodeStrategy *pixelDecodeStrategy, const string &tilesFsPath);

    void update(float elapsed) override;

    void draw(SDL_Renderer *renderer) override;

    void handle(const SDL_Event &event) override;

private:
    static constexpr int BOUND_X_TILES = 167;
    static constexpr int BOUND_Y_TILES = 155;
    static constexpr int MAP_FILE_SIZE = 13103;
    static constexpr int TILES_PER_ROW = 168;

    static constexpr int NPC_SPAWN_PERIOD = 10.000;

    float npcSpawnCounter = 0;

    static OverworldSpriteType::SpriteType getSpriteType(int tileTypeId);

    shared_ptr<OverworldTile> _playerTile;
    vector<shared_ptr<OverworldTile>> _tiles;
    SDL_Rect _camera;
    map<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>> _spritesMap;

    vector<shared_ptr<OverworldEnemy>> _enemies;
    bool _attackMode = false;

    void setCamera();

    static int toPixels(int tiles);

    static int toTiles(int pixels);

    void executeOnVisibleTiles(const function<void(OverworldTile *)> &);

    void moveOrAttack(int deltaX, int deltaY);

    void move(int deltaX, int deltaY);

    void attack(int deltaX, int deltaY);

    void enterPlace();

    static int getTileOffsetFromPositionInPixels(int xPx, int yPx);

    static int getTileOffset(int x, int y);

    void activateNpcs();

    void spawnNpcs();

    void setAttackMode(bool set);

    static string getCardinalPointFromDeltas(int deltaX, int deltaY);
};

