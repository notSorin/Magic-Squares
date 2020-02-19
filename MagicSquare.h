#pragma once
#include <glm.hpp>

using namespace glm;

const float MAGIC_SCALE = 50.0f;

class MagicSquare
{
public:
	MagicSquare(vec2 c1, vec2 c2, vec2 c3, vec2 c4);
	~MagicSquare();

	inline const vec2 & getC1() const {return _c1;}
	inline const vec2 & getC2() const {return _c2;}
	inline const vec2 & getC3() const {return _c3;}
	inline const vec2 & getC4() const {return _c4;}
	inline const vec3 & getColor() const {return _color;}

	//Returns the magic square contained within the current magic square.
	MagicSquare getMagicSquare() const;

private:
	vec2 _c1, _c2, _c3, _c4; //The square's corners.
	vec3 _color;
};