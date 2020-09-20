#include "DungeonScreen.h"
#include "../CommandDisplay.h"
#include "Door.h"
#include "Ladder.h"
#include "../common/ShapeUtils.h"
#include "../common/Fonts.h"
#include "../common/Colors.h"
#include "enemies/Thief.h"
#include <iostream>

using namespace std;

void DungeonScreen::update(float elapsed) {
    if (!_drawEnabled) {
        _drawCounter += elapsed;
        if (_drawCounter >= 100) {
            _drawEnabled = true;
            _drawCounter = 0;
        }
    }
}

void DungeonScreen::draw(SDL_Renderer *renderer) {
    ShapeUtils::drawRoundedCorners(renderer);
    ShapeUtils::drawDungeonBorders(renderer);

    _orientationLabel->loadFromRenderedText(Fonts::standard(), renderer, CardinalPointUtils::toString(
            _gameContext->getPlayer()->getDungeonOrientation()), Colors::TEXT_COLOR);
    _orientationLabel->render(renderer, 144, 150);

    _levelLabel->loadFromRenderedText(Fonts::standard(), renderer,
                                      "Level  " + to_string(_gameContext->getPlayer()->getDungeonLevel() + 1),
                                      Colors::TEXT_COLOR);
    _levelLabel->render(renderer, 272 / 2, -2);

    // TODO: not too happy with the viewport thingy
    SDL_Rect defaultViewport = {MAIN_VIEWPORT_PADDING, MAIN_VIEWPORT_PADDING, WIDTH, HEIGHT};
    SDL_RenderSetViewport(renderer, &defaultViewport);

    clearScreen(renderer);

    // the _drawEnabled flag controls drawing to the screen.
    // this is to have a flicker effect similar to the original game so that the player sees a small delay in the drawing after an action.
    if (!_drawEnabled) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    constexpr int DRAWING_PADDING = 8;

    if (_vision[0].feature == DungeonFeature::Door) {
        // We're standing inside a doorway, this screws up everything.
        // If looking through the doorway, we only care about the following two spaces: the next corridor space, and the wall after it.
        // Remember this whole dungeon design depends on everything being laid down in straight corridors, it's a mess!
        if (_vision.size() == 3) {
            // We're looking through the doorway.
            // Draw the arch and what's after it.

            // Draw arch first
            // Top
            SDL_RenderDrawLine(renderer, 16, 8, 16 + 272, 8);
            // Bottom left
            SDL_RenderDrawLine(renderer, 16, 135, 16 + 65, 135);
            SDL_RenderDrawLine(renderer, 80, 135, 80, 135 - 99);

            SDL_RenderDrawLine(renderer, 80, 36, 80 + 144, 36);

            SDL_RenderDrawLine(renderer, 80 + 144, 36, 80 + 144, 36 + 99);
            SDL_RenderDrawLine(renderer, 80 + 144, 36 + 99, 80 + 144 + 65, 36 + 99);

            // Draw what's after the arch, it should only be either a straight wall, a hidden door (looks like a wall) or another door.
            SDL_RenderDrawLine(renderer, 16 + 65, 54, 16 + 65 + 143, 54);
            SDL_RenderDrawLine(renderer, 16 + 65, 89, 16 + 65 + 143, 89);

            // If there is a door at the other side, draw it
            if (_vision[2].feature == DungeonFeature::Door) {
                SDL_RenderDrawLine(renderer, 134, 89, 134, 89 - 26);
                SDL_RenderDrawLine(renderer, 134, 89 - 26, 134 + 35, 89 - 26);
                SDL_RenderDrawLine(renderer, 134 + 35, 89 - 26, 134 + 35, 89 - 26 + 26);
            }
        } else {
            // We're inside a doorway, but facing the side walls, nothing to see but a wall
            SDL_RenderDrawLine(renderer, 16, 8, 16 + 272, 8);
            SDL_RenderDrawLine(renderer, 16, 135, 80 + 144 + 65, 135);
        }
    } else {
        // First draw all the walls
        if (_vision.size() == 2) {
            // 2 tiles of vision means the tile we are in right now, and the next tile is a wall/door (if it wasn't a wall, we'd be able to see past it)
            // x1 --> left point, x2 --> right point, y1 --> upper point, y2 --> lower point
            constexpr int oppositeWallX1 = 80;
            constexpr int oppositeWallY1 = 36;
            constexpr int oppositeWallX2 = oppositeWallX1 + 144 - 1;
            constexpr int oppositeWallY2 = oppositeWallY1 + 72 - 1;

            // draw the upper and lower lines of the opposite wall.
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX2, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, oppositeWallX2, oppositeWallY2);

            if (isWalledFeature(_vision[0].left)) {
                SDL_RenderDrawLine(renderer, UPPER_LEFT_X, UPPER_LEFT_Y, oppositeWallX1, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX1, oppositeWallY2);
                SDL_RenderDrawLine(renderer, LOWER_LEFT_X, LOWER_LEFT_Y, oppositeWallX1, oppositeWallY2);
            } else {
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, DRAWING_PADDING, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, DRAWING_PADDING, oppositeWallY2);
            }

            if (isWalledFeature(_vision[0].right)) {
                SDL_RenderDrawLine(renderer, UPPER_RIGHT_X, UPPER_RIGHT_Y, oppositeWallX2, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY1, oppositeWallX2, oppositeWallY2);
                SDL_RenderDrawLine(renderer, LOWER_RIGHT_X, LOWER_RIGHT_Y, oppositeWallX2, oppositeWallY2);
            } else {
                SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY1, WIDTH - DRAWING_PADDING, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY2, WIDTH - DRAWING_PADDING, oppositeWallY2);
            }
        } else {

            drawLeftWalls(renderer);
            drawRightWalls(renderer);

            // This is the vision "horizon"
            SDL_RenderDrawLine(renderer, 149, 72, 155, 72);
            SDL_RenderDrawLine(renderer, 149, 73, 155, 73);

            // If there is something at 5 spots away, it could either mean it's a wall, or is just the limit of visibility.
            if (_vision.size() == 5 && isWalledFeature(_vision[4].feature)) {
                SDL_Rect oppositeWallRect = {143, 69, 18, 7};

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderFillRect(renderer, &oppositeWallRect);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderDrawRect(renderer, &oppositeWallRect);
            } else if (_vision.size() == 4) {
                SDL_Rect oppositeWallRect = {134, 64, 36, 17};

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderFillRect(renderer, &oppositeWallRect);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderDrawRect(renderer, &oppositeWallRect);
            } else if (_vision.size() == 3) {
                SDL_Rect oppositeWallRect = {116, 55, 72, 35};

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderFillRect(renderer, &oppositeWallRect);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderDrawRect(renderer, &oppositeWallRect);
            }
        }
    }

    // draw sprites in reverse order so that the closer sprites are drawn on top of the farther ones
    int distance = _vision.size() - 1;
    while (distance >= 0) {
        auto tile = _vision[distance];

        if (tile.right == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Right);
        }

        if (tile.left == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Left);
        }

        if (tile.feature == DungeonFeature::Door) {
            if (distance != 0) {
                Door::drawFrontFacing(renderer, distance);
            }
        }

        if (tile.enemy != nullptr && !tile.enemy->isDead()) {
            tile.enemy->draw(renderer, distance);
        }

        if (tile.ladder != nullptr) {
            auto currentOrientation = _gameContext->getPlayer()->getDungeonOrientation();
            if (currentOrientation == CardinalPoint::East || currentOrientation == CardinalPoint::West) {
                Ladder::drawFromSide(renderer, distance, tile.ladder->goingUp);
            } else {
                Ladder::drawFront(renderer, distance, tile.ladder->goingUp);
            }
        }

        distance--;
    }
}

void DungeonScreen::handle(const SDL_Event &e) {
    auto player = _gameContext->getPlayer();

    if (e.type == SDL_KEYDOWN) {
        auto pressedKey = e.key.keysym.sym;

        switch (pressedKey) {
            case SDLK_UP:
                moveForward();
                break;
            case SDLK_DOWN:
                player->dungeonTurn(Direction::Right);
                player->dungeonTurn(Direction::Right);
                CommandDisplay::writeLn("Turn around", true);
                break;
            case SDLK_LEFT:
                player->dungeonTurn(Direction::Left);
                CommandDisplay::writeLn("Turn left", true);
                break;
            case SDLK_RIGHT:
                player->dungeonTurn(Direction::Right);
                CommandDisplay::writeLn("Turn right", true);
                break;
            case SDLK_a:
                doCombatRound(true);
                break;
            case SDLK_k:
                climbLadder();
                break;
            default:
                return;
        }

        _vision = _dungeon->getVisible(player->getDungeonLevel(), player->getDungeonX(), player->getDungeonY(),
                                       player->getDungeonOrientation());

        for (const auto &visibleTile: _vision) {
            if (visibleTile.enemy) {
                CommandDisplay::writeLn(visibleTile.enemy->getName(), false);
                // Only display the name of the first enemy in the conga line.
                break;
            }
        }

        _drawEnabled = false;
    }
}

void DungeonScreen::moveForward() {
    auto player = _gameContext->getPlayer();
    if (_vision[1].feature == DungeonFeature::Wall || _vision[1].enemy != nullptr) {
        CommandDisplay::writeLn("Forward - path blocked!", true);
        return;
    }

    // If we arrive to this point, we're either inside a door, or in a hallway and can move forward.
    player->dungeonMoveForward();
    CommandDisplay::writeLn("Forward", true);

    cout << "Moved to: " << player->getDungeonX() << ", " << player->getDungeonY() << "\n";
}

void DungeonScreen::drawLeftWalls(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer, 8, 0, 149, 72);
    SDL_RenderDrawLine(renderer, 8, 144, 149, 73);
}

void DungeonScreen::drawRightWalls(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer, 296, 0, 155, 72);
    SDL_RenderDrawLine(renderer, 296, 144, 155, 73);
}

void DungeonScreen::doCombatRound(bool playerAttacks) {
    if (playerAttacks) doPlayerAttack();
    doMonsterAttacks();
}

void DungeonScreen::doPlayerAttack() {
    // attack monster in front of player
    auto player = _gameContext->getPlayer();
    shared_ptr<Enemy> enemy = nullptr;

    for (const auto &tile: _vision) {
        if (tile.enemy != nullptr) {
            enemy = tile.enemy;
            break;
        }
    }

    if (enemy != nullptr) {
        CommandDisplay::writeLn("Attack with your bare hands", true);

        enemy->receiveDamage(1);
        if (enemy->isDead()) {
            CommandDisplay::writeLn("Hit! " + enemy->getName() + " killed!", false);
        } else {
            CommandDisplay::writeLn("Hit! 1 damage", false);
        }
    }
}

void DungeonScreen::doMonsterAttacks() {
    auto player = _gameContext->getPlayer();

    for (const auto &enemy: _dungeon->getLevelEnemies(player->getDungeonLevel())) {
        if ((enemy->getX() == player->getDungeonX() - 1 || enemy->getX() == player->getDungeonX() + 1) &&
            (enemy->getY() == player->getDungeonY() - 1 || enemy->getY() == player->getDungeonY() + 1)) {
            doMonsterAttack(enemy);
        }
    }
}

void DungeonScreen::doMonsterAttack(const shared_ptr<Enemy> &enemy) {
    auto player = _gameContext->getPlayer();

    CommandDisplay::writeLn("Attacked by " + enemy->getName() + "!", false);
    CommandDisplay::writeLn("Hit! " + to_string(enemy->getDamage()) + " damage!", false);

    player->receiveDamage(enemy->getDamage());

    if (player->isDead()) {
        CommandDisplay::writeLn("You are dead, nothing happens for now! :)", false);
    }
}

void DungeonScreen::climbLadder() {
    if (_vision[0].ladder == nullptr) {
        CommandDisplay::writeLn("K-Limb what?", true);
        return;
    }

    auto player = _gameContext->getPlayer();
    auto currentLevel = player->getDungeonLevel();
    auto ladder = _vision[0].ladder;
    if (ladder->goingUp) {
        if (currentLevel == 0) {
            _gameContext->setScreen(ScreenType::Overworld);
            CommandDisplay::writeLn("K-Limb up to level " + to_string(currentLevel), true);
        } else {
            player->setDungeonLevel(--currentLevel);
            CommandDisplay::writeLn("K-Limb up to level " + to_string(currentLevel + 1), true);
        }
    } else {
        player->setDungeonLevel(++currentLevel);
        CommandDisplay::writeLn("K-Limb down to level " + to_string(currentLevel + 1), true);
    }

    player->setDungeonX(ladder->toX);
    player->setDungeonY(ladder->toY);
}
