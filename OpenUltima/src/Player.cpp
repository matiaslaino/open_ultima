#include "Player.h"

void Player::dungeonTurn(Direction value) {
    if (value == Direction::Right) {
        switch (_dungeonOrientation) {
            case CardinalPoint::North:
                _dungeonOrientation = CardinalPoint::East;
                break;
            case CardinalPoint::East:
                _dungeonOrientation = CardinalPoint::South;
                break;
            case CardinalPoint::South:
                _dungeonOrientation = CardinalPoint::West;
                break;
            case CardinalPoint::West:
                _dungeonOrientation = CardinalPoint::North;
                break;
        }
    } else {
        switch (_dungeonOrientation) {
            case CardinalPoint::North:
                _dungeonOrientation = CardinalPoint::West;
                break;
            case CardinalPoint::West:
                _dungeonOrientation = CardinalPoint::South;
                break;
            case CardinalPoint::South:
                _dungeonOrientation = CardinalPoint::East;
                break;
            case CardinalPoint::East:
                _dungeonOrientation = CardinalPoint::North;
                break;
        }
    }
}

void Player::dungeonMoveForward() {
    switch (_dungeonOrientation) {
        case CardinalPoint::North:
            _dungeonY--;
            break;
        case CardinalPoint::East:
            _dungeonX++;
            break;
        case CardinalPoint::South:
            _dungeonY++;
            break;
        case CardinalPoint::West:
            _dungeonX--;
            break;
    }
}
