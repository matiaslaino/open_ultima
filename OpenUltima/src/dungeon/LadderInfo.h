#pragma once

struct LadderInfo {
public:
    int fromX, fromY, toX, toY;
    bool goingUp;

    LadderInfo(int fromX_, int fromY_, int toX_, int toY_, bool goingUp_) : fromX(fromX_), fromY(fromY_), toX(toX_),
                                                                            toY(toY_), goingUp(goingUp_) {}
};