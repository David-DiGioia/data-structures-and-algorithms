#include <iostream>
#include "dataStructures/Trie.h"
#include "algorithms/BinaryStrings.h"

int main()
{
	//// Trie
	//Trie trie;
	//trie.insert("hello");
	//std::cout << trie.contains("hem") << '\n';

	// Binary strings
	for (int i{ 0 }; i < 10; ++i)
		std::cout << nonConsecutiveOnes(i) << '\n';
}