#pragma once
#include <Windows.h>
#include "Box2D\Common\b2Math.h"


class Glyph {
public:
	Glyph(){}

	Glyph(char myChar) {
		_myChar = myChar;
		_pos = b2Vec2(0, 0);
	}

	Glyph(char myChar, b2Vec2 pos) {
		_myChar = myChar;
		_pos = pos;
	}

	Glyph(b2Vec2 pos) {
		_myChar = ' ';
		_pos = pos;
	}

	void setPos(b2Vec2 newPos) {
		_pos = newPos;
	}

	b2Vec2 getPos() {
		return _pos;
	}

	void setGlyph(char newChar) {
		_myChar = newChar;
	}

	char getGlyph() {
		return _myChar;
	}

private:
	char _myChar;
	b2Vec2 _pos;
};