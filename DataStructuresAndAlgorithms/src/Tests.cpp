#include "Tests.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>

#include "dataStructures/Vec.h"
#include "algorithms/SelfAvoidingWalk.h"
#include "algorithms/PathFinding.h"

void printTabs(int n, std::ofstream& file)
{
	for (int i{ 0 }; i < n; ++i)
	{
		std::cout << '\t';
		file << '\t';
	}
}

void testSelfAvoidingWalk()
{
	std::ofstream logfile("SelfAvoidingWalkLog.txt");
	for (int n{ 1 }; n <= 18; ++n)
	{
		std::cout << "n: " << n << '\n';
		if (logfile.is_open())	logfile << "n: " << n << '\n';
		else std::cerr << "Error writing to log file\n";

		std::vector<unsigned long long> walks{ countSaw(n) };
		int lineLength{ 1 };
		int lineCount{ 0 };
		int row{ 0 };
		bool newRow{ true };
		for (unsigned int i{ 0 }; i < walks.size(); ++i)
		{
			if (newRow)
			{
				printTabs(n / 2 - row, logfile);
				newRow = false;
			}

			std::cout << walks[i] << (i == walks.size() - 1 ? "" : "\t\t");
			if (logfile.is_open())	logfile << walks[i] << (i == walks.size() - 1 ? "" : "\t\t");
			else std::cerr << "Error writing to log file\n";
			if (++lineCount == lineLength)
			{
				newRow = true;
				++lineLength;
				lineCount = 0;
				const char* s{ ++row == n / 2 && n % 2 == 0 ? "\n0\t\t" : "\n" };
				std::cout << s;
				if (logfile.is_open())	logfile << s;
				else std::cerr << "Error writing to log file\n";
			}
		}
		std::cout << "\n\n";
		if (logfile.is_open())	logfile << "\n\n";
		else std::cerr << "Error writing to log file\n";
	}
	logfile.close();
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