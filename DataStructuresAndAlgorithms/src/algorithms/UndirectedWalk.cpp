#include "UndirectedWalk.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2)
{
	return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

void printSequenceDifference(std::vector<int> & v)
{
	int loopCount{ (int)v.size() - 1 };
	for (int i{ 0 }; i < loopCount; ++i)
	{
		for (int n : v)
			std::cout << n << " ";
		std::cout << '\n';
		std::adjacent_difference(v.begin(), v.end(), v.begin()), v.end();
		v.erase(v.begin());
	}

}
