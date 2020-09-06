#include "OverworldScreen.h"
#include "TileTypeLoader.h"
#include "../common/graphics/PixelDecodeStrategy.h"
#include "Constants.h"
#include "TileAnimation.h"
#include "../common/Fonts.h"
#include "../CommandDisplay.h"

void OverworldScreen::init(SDL_Renderer *renderer, PixelDecodeStrategy *pixelDecodeStrategy, const string &tilesFsPath) {
    _tiles.clear();
    _spritesMap.clear();

    // load all sprite types.
    auto spriteLoader = make_unique<TileTypeLoader>();
    auto spriteTypes = spriteLoader->loadOverworldSprites(tilesFsPath, pixelDecodeStrategy, renderer);

    // write to map so it's easier to find the sprite type by type name.
    for (const auto &spriteType : spriteTypes) {
        _spritesMap.insert(pair<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>>(spriteType->getType(),
                                                                                                  spriteType));
    }

    // TODO: get this from parameter.
    string mapFileLocation = R"(F:\GOGLibrary\Ultima 1\MAP.BIN)";

    auto file = SDL_RWFromFile(mapFileLocation.c_str(), "r+b");
    auto buffer = new uint8_t[MAP_FILE_SIZE];
    SDL_RWread(file, buffer, 1, MAP_FILE_SIZE);
    SDL_RWclose(file);

    auto currentX = -1;
    auto currentY = 0;

    // All water and static tiles share the same animation (water needs to scroll at the same time, and NOP tiles don't do anything)
    auto defaultSharedAnimation = make_shared<TileAnimation>();

    // map file format is one byte contains the data of two tiles, one per nibble, so shift and mask them.
    for (int i = 0; i < MAP_FILE_SIZE; i++) {
        auto byte = buffer[i];
        auto idTileNibble1 = byte >> 4;
        auto idTileNibble2 = byte & 0b00001111;
        auto spriteType1 = getSpriteType(idTileNibble1);
        auto spriteType2 = getSpriteType(idTileNibble2);
        auto sprite1 = _spritesMap.find(spriteType1)->second;
        auto sprite2 = _spritesMap.find(spriteType2)->second;

        currentX++;
        if (currentX > BOUND_X_TILES) {
            currentX = 0;
            currentY++;
        }
        auto x1 = currentX;
        auto y1 = currentY;

        currentX++;
        if (currentX > BOUND_X_TILES) {
            currentX = 0;
            currentY++;
        }
        auto x2 = currentX;
        auto y2 = currentY;

        // water tiles share the same scrolling animation instance so they all animate at the same time
        auto animation = sprite1->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation
                                                                                                : make_shared<TileAnimation>();
        auto tile1 = make_shared<OverworldTile>(toPixels(x1), toPixels(y1), sprite1, animation);
        _tiles.push_back(tile1);

        animation = sprite2->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation
                                                                                           : make_shared<TileAnimation>();
        auto tile2 = make_shared<OverworldTile>(toPixels(x2), toPixels(y2), sprite2, animation);
        _tiles.push_back(tile2);
    }

    _playerTile = make_shared<OverworldTile>(toPixels(_gameContext->getPlayer()->getOverworldX()),
                                    toPixels(_gameContext->getPlayer()->getOverworldY()),
                                    _spritesMap.find(OverworldSpriteType::SpriteType::PLAYER)->second,
                                    defaultSharedAnimation);

    delete[] buffer;
}

void OverworldScreen::update(float elapsed) {
    // scrolling animation (water) needs to be animated on its own.
    TileAnimation::updateScrolling(elapsed);

    executeOnVisibleTiles([elapsed](OverworldTile *tile) -> void { tile->update(elapsed); });
}

void OverworldScreen::draw(SDL_Renderer *renderer) {
    // why do i need to declare a variable for a capture? fuck!
    auto camera = _camera;

    // this is a lambda expression, and i thought java was verbose!
    executeOnVisibleTiles([renderer, camera](Tile *tile) -> void { tile->draw(renderer, camera); });

    _playerTile->draw(renderer, camera);
}

void OverworldScreen::move(int deltaX, int deltaY) {
    int playerX = _gameContext->getPlayer()->getOverworldX() + deltaX;
    int playerY = _gameContext->getPlayer()->getOverworldY() + deltaY;

    // don't allow the player to move outside of overworld bounds (should this game allow world map wrapping?)
    if (playerX < 0) playerX = 0;
    if (playerX > BOUND_X_TILES) playerX = BOUND_X_TILES;
    if (playerY < 0) playerY = 0;
    if (playerY > BOUND_Y_TILES) playerY = BOUND_Y_TILES;

    if (playerX < _gameContext->getPlayer()->getOverworldX()) {
        CommandDisplay::write("West", true);
    } else if (playerX > _gameContext->getPlayer()->getOverworldX()) {
        CommandDisplay::write("East", true);
    } else if (playerY > _gameContext->getPlayer()->getOverworldY()) {
        CommandDisplay::write("South", true);
    } else if (playerY < _gameContext->getPlayer()->getOverworldY()) {
        CommandDisplay::write("North", true);
    }

    _gameContext->getPlayer()->setOverworldX(playerX);
    _gameContext->getPlayer()->setOverworldY(playerY);

    _playerTile->setCoordinates(toPixels(playerX), toPixels(playerY));

    // re-center camera on player if possible
    setCamera();
}

void OverworldScreen::enterDungeon() {
    _gameContext->enterDungeon();
}

void OverworldScreen::handle(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        auto pressedKey = event.key.keysym.sym;

        switch (pressedKey) {
            case SDLK_UP:
                move(0, -1);
                break;
            case SDLK_DOWN:
                move(0, 1);
                break;
            case SDLK_LEFT:
                move(-1, 0);
                break;
            case SDLK_RIGHT:
                move(1, 0);
                break;
            case SDLK_e:
                enterDungeon();
                break;
        }
    }
}

void OverworldScreen::setCamera() {
    _camera.x = toPixels(_gameContext->getPlayer()->getOverworldX() - (DISPLAY_SIZE_TILES_WIDTH - 1) / 2);
    _camera.y = toPixels(_gameContext->getPlayer()->getOverworldY() - (DISPLAY_SIZE_TILES_HEIGHT - 1) / 2);

    int cameraBoundX = toPixels(BOUND_X_TILES);
    int cameraBoundY = toPixels(BOUND_Y_TILES);

    // make sure the camera doesn't show where the world ends!
    if (_camera.x < 0) _camera.x = 0;
    if (_camera.y < 0) _camera.y = 0;
    if (_camera.x + toPixels(DISPLAY_SIZE_TILES_WIDTH) > cameraBoundX) _camera.x = cameraBoundX -
                                                                                   toPixels(DISPLAY_SIZE_TILES_WIDTH);
    if (_camera.y + toPixels(DISPLAY_SIZE_TILES_HEIGHT) > cameraBoundY) _camera.y = cameraBoundY -
                                                                                    toPixels(DISPLAY_SIZE_TILES_HEIGHT);
}

int OverworldScreen::toPixels(int tiles) {
    return tiles * TILE_WIDTH;
}

int OverworldScreen::toTiles(int pixels) {
    return pixels / TILE_WIDTH;
}

void OverworldScreen::executeOnVisibleTiles(const function<void(OverworldTile *)>& func) {
    int tileStartOffset = toTiles(_camera.y) * TILES_PER_ROW + toTiles(_camera.x);
    int offset = tileStartOffset;

    for (int y = 0; y < DISPLAY_SIZE_TILES_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_SIZE_TILES_WIDTH; x++) {
            int tileOffset = (offset + x);
            if (tileOffset >= _tiles.size()) continue;

            auto tile = _tiles[tileOffset];
            func(tile.get());
        }
        offset += TILES_PER_ROW;
    }
}

OverworldSpriteType::SpriteType OverworldScreen::getSpriteType(int tileTypeId) {
    switch (tileTypeId) {
        case 0: {
            return OverworldSpriteType::SpriteType::WATER;
        }
            break;
        case 1: {
            return OverworldSpriteType::SpriteType::GRASS;
        }
            break;
        case 2: {
            return OverworldSpriteType::SpriteType::FOREST;
        }
            break;
        case 3: {
            return OverworldSpriteType::SpriteType::MOUNTAIN;
        }
            break;
        case 4: {
            return OverworldSpriteType::SpriteType::CASTLE;
        }
            break;
        case 5: {
            return OverworldSpriteType::SpriteType::SIGNPOST;
        }
            break;
        case 6: {
            return OverworldSpriteType::SpriteType::TOWN;
        }
            break;
        case 7: {
            return OverworldSpriteType::SpriteType::DUNGEON_ENTRANCE;
        }
            break;
    }

    throw "Error!";
}