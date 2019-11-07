#include "UndirectedWalk.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>

int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2)
{
	return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

int pointsDistance(const Vec2<int>& pos, int n)
{
	if (pos.x <= 0)
		return !(n % 2) - pos.x + 1 + std::abs(pos.y);
	return (n % 2 != pos.x % 2) + std::abs(pos.y);
}

static void countUndirectedWalkRec(const int n, int level, unsigned long long* count, Vec2<int>& pos,
	std::unordered_set<Vec2<int>, HashVec2i>& visited)
{
	if (level == n)
	{
		if (pos.y == 0 && pos.x > 0)
			++count[(pos.x + 1)/2 - 1];
		return;
	}

	// Add one to compensate for passing in n-1, since we split up the walk for symmetry
	if (pointsDistance(pos, n + 1) > n - level)
		return;

	for (const auto& dir : DIRECTIONS)
	{
		Vec2<int> node{ pos + dir };
		if (visited.find(node) == visited.end())
		{
			visited.insert(node);
			countUndirectedWalkRec(n, level + 1, count, node, visited);
			visited.erase(node);
		}
	}
}

std::vector<unsigned long long> countUndirectedWalk(int n)
{
	int len{ (n + 1) / 2 };

	unsigned long long* count{ new unsigned long long[len] {} };
	unsigned long long* symCount{ new unsigned long long[len] {} };
	Vec2<int> pos{ 0, 0 };
	std::unordered_set<Vec2<int>, HashVec2i> visited;
	visited.insert(pos);

	// left and right
	int i{ 1 };
	while (++i <= 3)
	{
		Vec2<int> dir{ pos + DIRECTIONS[i] };
		visited.insert(dir);
		countUndirectedWalkRec(n - 1, 0, count, dir, visited);
		visited.erase(dir);
	}

	// up
	Vec2<int> up{ pos + DIRECTIONS[0] };
	visited.insert(up);
	countUndirectedWalkRec(n - 1, 0, symCount, up, visited);
	visited.erase(up);

	std::vector<unsigned long long> result(len);
	for (int i{ 0 }; i < len; ++i)
		result[i] = count[i] + 2 * symCount[i];
	delete[] count;
	delete[] symCount;

	return result;
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
