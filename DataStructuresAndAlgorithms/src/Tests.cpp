#include "Tests.h"
#include <iostream>
#include <unordered_set>
#include <vector>

#include "dataStructures/Vec.h"
#include "algorithms/SelfAvoidingWalk.h"
#include "algorithms/PathFinding.h"

void testSelfAvoidingWalk()
{
	for (int n{ 1 }; n <= 20; ++n)
	{
		std::cout << "n: " << n << '\n';

		std::vector<unsigned long long> walks{ countSaw(n) };
		int lineLength{ 1 };
		int lineCount{ 0 };
		for (unsigned int i{ 0 }; i < walks.size(); ++i)
		{
			std::cout << walks[i] << (i == walks.size() - 1 ? "" : "\t");
			if (++lineCount == lineLength)
			{
				++lineLength;
				lineCount = 0;
				std::cout << '\n';
			}
		}
		std::cout << "\n\n";
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