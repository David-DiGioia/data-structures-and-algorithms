#include "Tests.h"
#include <iostream>
#include "dataStructures/Vec.h"
#include "algorithms/UndirectedWalk.h"

void testUndirectedWalk()
{
	//std::vector<int> vec{1, 18, 660, 8064};
	//printSequenceDifference(vec);
	//return 0;

	for (int n{ 0 }; n < 30; ++n)
	{
		std::cout << "n: " << n << '\n';
		for (int x{ 1 }; x <= n; ++x)
		{
			if (n % 2 == 0 && x % 2 != 0 || n % 2 != 0 && x % 2 == 0)
				continue;
			auto base{ [x](const Vec2<int> & pos) { return pos == Vec2<int>{x, 0}; } };
			auto dist{ [x](const Vec2<int> & pos) { return pathDistance(pos, Vec2<int>{x, 0}); } };
			int walks{ n == x ? 1 : countUndirectedWalk(n, base, dist) };
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