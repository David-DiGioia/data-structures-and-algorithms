#include <iostream>
#include "dataStructures/Trie.h"

int main()
{
	Trie trie;
	trie.insert("hello");
	std::cout << trie.contains("hem") << '\n';
}