#include <iostream>
#include "Tests.h"
#include <chrono>

int main()
{
	std::chrono::steady_clock::time_point begin{ std::chrono::steady_clock::now() };
	testUndirectedWalk();
	std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
	auto time{ std::chrono::duration_cast<std::chrono::microseconds>(end - begin) };
	std::cout << "Execution finished in " << time.count() << " microseconds.\n";
	std::cin.get();
}
