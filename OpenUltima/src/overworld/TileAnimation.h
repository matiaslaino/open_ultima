#pragma once

#include <vector>
#include <SDL.h>

using namespace std;

class TileAnimation {
public:
    enum class AnimationType {
        NOP, SWAP, SCROLLING
    };

    struct RenderQuad {
    public:
        RenderQuad(SDL_Rect source_, SDL_Rect target_) : source(source_), target(target_) {}

        SDL_Rect source;
        SDL_Rect target;
    };

    static void updateScrolling(float elapsed);

    void update(float elapsed, AnimationType animationType, SDL_Rect box);

    vector<TileAnimation::RenderQuad> getRenderQuads(SDL_Renderer *renderer,
                                                     AnimationType animationType, SDL_Rect spriteBox,
                                                     SDL_Rect textureSpriteSource, int swapOffset) const;

private:
    static double _scroll;
    float _swapCounter = 0;
    bool _swapped = false;
};

