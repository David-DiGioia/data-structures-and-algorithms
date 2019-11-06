#pragma once
#include <vector>
#include <unordered_set>
#include "../dataStructures/Vec.h"

// Minimum path distance between 2 points. In other words, the
// number of steps needed to reach pos2 from pos1
int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2);

// Grid of possible points a path of length n my reach
std::unordered_set<Vec2<int>, HashVec2i> getGrid(int n);


// Recursive function to count number of undirected walks
template<class BaseFn, class TermFn>
static void countUndirectedWalkRec(const int n, int level, unsigned long long& count, Vec2<int>& pos,
	std::unordered_set<Vec2<int>, HashVec2i>& visited, const BaseFn& base, const TermFn& term)
{
	if (level == n)
	{
		if (base(pos))
			++count;
		return;
	}

	if (term(pos, n - level, visited))
		return;

	//if (term(pos, n - level))
	//	return;

	for (const auto& dir : DIRECTIONS)
	{
		Vec2<int> node{ pos + dir };
		if (visited.find(node) == visited.end())
		{
			visited.insert(node);
			countUndirectedWalkRec(n, level + 1, count, node, visited, base, term);
			visited.erase(node);
		}
	}
}

// Count number of undirected walks. BaseFn decides if that means counting all
// walks ending on y=0 or just certain arbitrary points.
// BaseFn returns true if a base case is reached. TermFn returns true if we should
// terminate the search early. For example, if no paths are possible
template<class BaseFn, class TermFn>
unsigned long long countUndirectedWalk(int n, BaseFn base, TermFn term)
{
	unsigned long long count{ 0 };
	Vec2<int> pos{ 0, 0 };
	std::unordered_set<Vec2<int>, HashVec2i> visited;
	visited.insert(pos);

	countUndirectedWalkRec(n, 0, count, pos, visited, base, term);
	return count;
}

// Repeatedly take the adjacent difference of a vector, printing at each step.
// This is helpful to tell what degree a polynomial is.
void printSequenceDifference(std::vector<int>& v);

void printPolynomial(int degree);
