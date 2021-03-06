#pragma once

#include "common/graphics/LTexture.h"
#include <memory>
#include "Player.h"
#include <vector>
#include <string>

using namespace std;

class CommandDisplay {
public:
    static constexpr int POSITION_X = 0;
    static constexpr int POSITION_Y = 160;
    static constexpr int WIDTH = 241;
    static constexpr int HEIGHT = 40;
    static constexpr int MAX_LINE_CHARS = 29;

    static void writeLn(const string &str, bool isPlayerAction);

    static void write(const string &str);

    explicit CommandDisplay(SDL_Renderer *renderer);

    void draw(SDL_Renderer *renderer);

private:
    static constexpr int MAX_LINES = 3;

    static vector<tuple<string, bool>> _text;
    static string _promptText;

    unique_ptr<LTexture> _background;
    shared_ptr<LTexture> _actionIcon;
    unique_ptr<LTexture> _line1;
    unique_ptr<LTexture> _line2;
    unique_ptr<LTexture> _line3;
    unique_ptr<LTexture> _promptLine;
};

