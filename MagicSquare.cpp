#include "MagicSquare.h"
#include <ctime>

MagicSquare::MagicSquare(vec2 c1, vec2 c2, vec2 c3, vec2 c4)
{
	_c1 = c1;
	_c2 = c2;
	_c3 = c3;
	_c4 = c4;

	//Each magic square has a random color.
	_color.r = rand() / (float)RAND_MAX;
	_color.g = rand() / (float)RAND_MAX;
	_color.b = rand() / (float)RAND_MAX;
}

MagicSquare::~MagicSquare()
{

}

MagicSquare MagicSquare::getMagicSquare() const
{
	vec2 c1 = _c1 + (normalize(_c4 - _c1) * MAGIC_SCALE);
	vec2 c2 = _c2 + (normalize(_c1 - _c2) * MAGIC_SCALE);
	vec2 c3 = _c3 + (normalize(_c2 - _c3) * MAGIC_SCALE);
	vec2 c4 = _c4 + (normalize(_c3 - _c4) * MAGIC_SCALE);

	return MagicSquare(c1, c2, c3, c4);
}