#pragma once
#include <vector>
#include <set>
#include "../dataStructures/Vec.h"

// Minimum path distance between 2 points. In other words, the
// number of steps needed to reach pos2 from pos1
int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2);

// Recursive function to count number of undirected walks
template<class BaseFn, class DistFn>
static void countUndirectedWalkRec(const int n, int level, int& count, Vec2<int>& pos, std::set<Vec2<int>>& visited, const BaseFn& base, const DistFn& dist)
{
	if (dist(pos) > n - level)
		return;

	if (level == n)
	{
		if (base(pos))
			++count;
		return;
	}

	Vec2<int> right{ pos + Vec2<int>{ 1, 0 } };
	Vec2<int> left{ pos + Vec2<int>{ -1, 0 } };
	Vec2<int> up{ pos + Vec2<int>{ 0, 1 } };
	Vec2<int> down{ pos + Vec2<int>{ 0, -1 } };

	if (visited.find(right) == visited.end())
	{
		visited.insert(right);
		countUndirectedWalkRec(n, level + 1, count, right, visited, base, dist);
		visited.erase(right);
	}
	if (visited.find(left) == visited.end())
	{
		visited.insert(left);
		countUndirectedWalkRec(n, level + 1, count, left, visited, base, dist);
		visited.erase(left);
	}
	if (visited.find(up) == visited.end())
	{
		visited.insert(up);
		countUndirectedWalkRec(n, level + 1, count, up, visited, base, dist);
		visited.erase(up);
	}
	if (visited.find(down) == visited.end())
	{
		visited.insert(down);
		countUndirectedWalkRec(n, level + 1, count, down, visited, base, dist);
		visited.erase(down);
	}
}

// Count number of undirected walks. BaseFn decides if that means counting all
// walks ending on y=0 or just certain arbitrary points.
// BaseFn returns true if a base case is reached. DistFn returns path distance
// to target point, so we can break early if we know we can't make it
template<class BaseFn, class DistFn>
int countUndirectedWalk(int n, BaseFn base, DistFn dist)
{
	int count{ 0 };
	Vec2<int> pos{ 0, 0 };
	std::set<Vec2<int>> visited;
	visited.insert(pos);

	countUndirectedWalkRec(n, 0, count, pos, visited, base, dist);
	return count;
}

// Repeatedly take the adjacent difference of a vector, printing at each step.
// This is helpful to tell what degree a polynomial is.
void printSequenceDifference(std::vector<int>& v);
