#include "UndirectedWalk.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2)
{
	return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

std::unordered_set<Vec2<int>, HashVec2i> getGrid(int n)
{
	std::unordered_set<Vec2<int>, HashVec2i> grid;
	if (n == 0)
	{
		grid.insert(Vec2<int>{0, 0});
		return grid;
	}
	if (n == 1)
	{
		grid.insert(Vec2<int>{-1, 0});
		grid.insert(Vec2<int>{0, 0});
		grid.insert(Vec2<int>{1, 0});
		return grid;
	}
	grid = getGrid(n - 1);

	if (n % 2 == 1)
	{
		grid.insert(Vec2<int>{0, n / 2});
		grid.insert(Vec2<int>{0, -n / 2});
	}

	auto gridCopy{ grid };
	for (const auto& node : grid)
	{
		Vec2<int> right{ node + Vec2<int>{1, 0} };
		Vec2<int> left{ node + Vec2<int>{-1, 0} };
		if (gridCopy.find(right) == gridCopy.end())
			gridCopy.insert(right);
		if (gridCopy.find(left) == gridCopy.end())
			gridCopy.insert(left);
	}
	return gridCopy;
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

void printPolynomial(int degree)
{
	for (int i{ degree }; i >= 0; --i)
	{
		std::cout << "x" << (degree - i + 1) << "*x^" << i;
		if (i != 0)
			std::cout << " + ";
	}
}
