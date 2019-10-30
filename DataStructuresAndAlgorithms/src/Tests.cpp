#include "Tests.h"
#include <iostream>
#include "dataStructures/Vec.h"
#include "algorithms/UndirectedWalk.h"

void testUndirectedWalk()
{
	printPolynomial(14);
	return;

	for (int n{ 27 }; n < 100; ++n)
	{
		std::cout << "n: " << n << '\n';
		for (int x{ 1 }; x <= n; ++x)
		{
			if (n % 2 == 0 && x % 2 != 0 || n % 2 != 0 && x % 2 == 0)
				continue;
			auto base{ [x](const Vec2<long long> & pos) { return pos == Vec2<long long>{x, 0}; } };
			auto dist{ [x](const Vec2<long long> & pos) { return pathDistance(pos, Vec2<long long>{x, 0}); } };
			long long walks{ n == x ? 1 : countUndirectedWalk(n, base, dist) };
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