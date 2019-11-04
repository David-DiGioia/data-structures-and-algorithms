#include "Vec.h"

size_t HashVec2i::operator()(const Vec2<int>& v) const
{
	long long temp{ ((long long)v.x) ^ (((long long)v.y) << 32) };
	return hash(temp);
}