#include "Tests.h"
#include <iostream>
#include <unordered_set>
#include "dataStructures/Vec.h"
#include "algorithms/UndirectedWalk.h"
#include "algorithms/PathFinding.h"

void testUndirectedWalk()
{
	for (int n{ 1 }; n <= 18; ++n)
	{
		std::cout << "n: " << n << '\n';
		std::unordered_set<Vec2<int>, HashVec2i> grid{ getGrid(n) };

		for (int x{ 1 }; x <= n; ++x)
		{
			if (n % 2 == 0 && x % 2 != 0 || n % 2 != 0 && x % 2 == 0)
				continue;
			Vec2<int> end{ x, 0 };
			auto base{ [&end](const Vec2<int> & pos) { return pos == end; } };
			//auto term{ [&, end, grid](const Vec2<int> & pos, int len, std::unordered_set<Vec2<int>, HashVec2i> visited) {
			//	//return !floodFillCanReach(pos, end, len, grid, visited);
			//	return pathDistance(pos, end) > len;
			//} };

			auto term{ [&, end](const Vec2<int>& pos, int len) {
				//return !floodFillCanReach(pos, end, len, grid, visited);
				return pathDistance(pos, end) > len;
			} };

			unsigned long long walks{ n == x ? 1 : countUndirectedWalk(n, base, term) };
			std::cout << "(" << x << "," << walks << "),";
		}
		std::cout << '\n';
	}
}

void testTrie()
{
	Trie trie;
	trie.insert("hello");
	std::cout << trie.contains("hem") << '\n';
}

void testNonConsecutiveOnes()
{
	for (int i{ 0 }; i < 10; ++i)
		std::cout << nonConsecutiveOnes(i) << '\n';
}