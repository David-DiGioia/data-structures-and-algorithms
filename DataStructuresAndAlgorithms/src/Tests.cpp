#include "Tests.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include "dataStructures/Vec.h"
#include "algorithms/UndirectedWalk.h"
#include "algorithms/PathFinding.h"

void testUndirectedWalk()
{
	for (int n{ 30 }; n <= 50; ++n)
	{
		std::cout << "n: " << n << '\n';

		std::vector<unsigned long long> walks{ countUndirectedWalk(n) };
		for (unsigned int i{ 0 }; i < walks.size(); ++i)
			std::cout << "(" << (n % 2 == 0 ? 2*(i+1) : 2*i + 1) << "," << walks[i] << (i == walks.size() - 1 ? ")" : "),");
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