#pragma once

#include <string>

using namespace std;

enum class CardinalPoint {
    East, West, North, South
};

class CardinalPointUtils {
public:
    static string toString(CardinalPoint cardinalPoint) {
        switch (cardinalPoint) {
            case CardinalPoint::East:
                return "East";
            case CardinalPoint::West:
                return "West";
            case CardinalPoint::North:
                return "North";
            case CardinalPoint::South:
                return "South";
        }
    }
};