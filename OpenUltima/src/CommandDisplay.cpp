#include "CommandDisplay.h"
#include "common/Fonts.h"
#include "common/Colors.h"
#include "ShapeUtils.h"

vector<tuple<string, bool>> CommandDisplay::_text;

void CommandDisplay::write(string str, bool isPlayerAction)
{
	_text.push_back(make_tuple(str, isPlayerAction));
	if (_text.size() > MAX_LINES) {
		_text.erase(_text.begin());
	}
}

CommandDisplay::CommandDisplay(SDL_Renderer* renderer)
{
	_background = make_unique<LTexture>();
	_background->loadFromColor(renderer, WIDTH, HEIGHT, 0, 0, 0, 0);

	_line1 = make_unique<LTexture>();
	_line2 = make_unique<LTexture>();
	_line3 = make_unique<LTexture>();

	_actionIcon = ShapeUtils::arrow(renderer, ShapeUtils::Direction::Right);
}

void CommandDisplay::draw(SDL_Renderer* renderer)
{
	_background->render(renderer, 0, 0);

	int lineIndex = _text.size() - 1;

	constexpr int LINE_HEIGHT = 8;
	constexpr int PADDING_LEFT = 8;
	constexpr int PADDING_TOP = 6;
	constexpr int PADDING_FONT = 2;

	int offset = LINE_HEIGHT * 2;

	if (lineIndex >= 0) {
		auto [line, playerAction] = _text.at(lineIndex--);
		_line3->loadFromRenderedText(Fonts::standard(), renderer, line, Colors::TEXT_COLOR);
		if (playerAction) {
			_actionIcon->render(renderer, 0, offset + PADDING_TOP + PADDING_FONT);
		}
		_line3->render(renderer, PADDING_LEFT, offset + PADDING_TOP);
		offset -= LINE_HEIGHT;
	}
	
	if (lineIndex >= 0) {
		auto [line, playerAction] = _text.at(lineIndex--);
		_line2->loadFromRenderedText(Fonts::standard(), renderer, line, Colors::TEXT_COLOR);
		if (playerAction) {
			_actionIcon->render(renderer, 0, offset + PADDING_TOP + PADDING_FONT);
		}
		_line2->render(renderer, PADDING_LEFT, offset + PADDING_TOP);
		offset -= LINE_HEIGHT;
	}

	if (lineIndex >= 0) {
		auto [line, playerAction] = _text.at(lineIndex--);
		_line1->loadFromRenderedText(Fonts::standard(), renderer, line, Colors::TEXT_COLOR);
		if (playerAction) {
			_actionIcon->render(renderer, 0, offset + PADDING_TOP + PADDING_FONT);
		}
		_line1->render(renderer, PADDING_LEFT, offset + PADDING_TOP);
		offset -= LINE_HEIGHT;
	}

	_actionIcon->render(renderer, 0, PADDING_TOP + LINE_HEIGHT * 3 + PADDING_FONT);
}
