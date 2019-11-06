#pragma once
#include <unordered_set>
#include "../dataStructures/Vec.h"

bool floodFillCanReach(const Vec2<int>& start, const Vec2<int>& end, int length,
	const std::unordered_set<Vec2<int>, HashVec2i>& grid, const std::unordered_set<Vec2<int>, HashVec2i>& visited);
