#pragma once
#include "Glyph.h"
#include "Box2D\Common\b2Math.h"
#include <vector>

#define Glyphset std::vector<Glyph>

/*
	Simple Entity class with glyphset (sprite) and position.
*/
class Entity {
public:
	Entity() {}
	// Init with pose
	Entity(Glyphset pose) {
		_glyphset = pose;
		_pos = b2Vec3(0, 0, 0);
	}

	// Init with pos
	Entity(b2Vec3 pos) {
		_glyphset = Glyphset({Glyph(' ')}); // Default pose. space does not get rendered
		_pos = pos;
	}

	// Init with both
	Entity(Glyphset pose, b2Vec3 pos) {
		_glyphset = pose;
		_pos = pos;
	}

	Glyphset* getGlyphset() {
		return &_glyphset;
	}

	void setGlyphset(Glyphset newGlyphset) {
		_glyphset = newGlyphset;
	}

	b2Vec3 getPos() {
		return _pos;
	}

	void setPos(b2Vec3 newPos) {
		_pos = newPos;
	}

	Entity* isCollidingWith;
	bool markForDeletion = false;
private:
	Glyphset _glyphset;
	b2Vec3 _pos;
	
};