#include "UndirectedWalk.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <utility>

unsigned int threadFlags{ 1 }; // 1 since parent thread gets a slot
const unsigned int threadCount{ std::thread::hardware_concurrency() };
const unsigned int threadsFull{ (1u << threadCount) - 1u };
std::mutex mtx;
std::condition_variable cond;

int triangleNumber(int n)
{
	return n * (n + 1) / 2;
}

int uniquePoints(int n)
{
	// (2*n^2 + 10*n + 3 + (-1)^n * (2*n - 3))/16
	return (2 * n * n + 10 * n + 3 + (n % 2 == 0 ? 1 : -1) * (2 * n - 3)) / 16;

	//if (n == 0) return 0;
	//if (n % 2 == 0) return uniquePoints(n - 2) + (n / 2) + 1;
	//else return uniquePoints(n - 1) + 1;
}

int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2)
{
	return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

int pointsDistance(const Vec2<int>& pos, int n)
{
	if (pos.x <= 0) return !(n % 2) - pos.x + 1 + std::abs(pos.y);
	return (n % 2 != pos.x % 2) + std::abs(pos.y);
}

int uniquePointsDistance(const Vec2<int>& pos, int n)
{
	if (pos.x <= 0) return (n % 2) - pos.x + std::abs(pos.y);
	if (pos.y <= 0) return (n % 2 != pos.x % 2) - pos.y;
	if (pos.y >= pos.x - (n % 2) && pos.x <= (n / 2) + (n % 2)) return pos.y - pos.x + (n % 2);
	if (pos.y >= n - pos.x && pos.x >= (n / 2) + (n % 2)) return pos.y - n + pos.x;
	return (pos.x % 2) ^ (pos.y % 2) ^ (n % 2);
}

static void countSawChildRec(const int n, int level, unsigned long long* count, Vec2<int>& pos,
	std::vector<std::unordered_set<Vec2<int>, HashVec2i>>& visited, const unsigned int idx)
{
	int dist{ uniquePointsDistance(pos, n) };

	if (level == n)
	{
		// subtract (pos.y == 0) since bottom row of unique triangle is missing first entry
		if (dist == 0)
			++count[triangleNumber((n / 2) - pos.y) - (pos.y == 0 && n % 2 == 0) + (pos.x - pos.y) / 2 + uniquePoints(n) * idx];
		return;
	}

	if (dist > n - level)
		return;

	for (const auto& dir : DIRECTIONS)
	{
		Vec2<int> node{ pos + dir };
		if (visited[idx].find(node) == visited[idx].end())
		{
			visited[idx].insert(node);
			countSawChildRec(n, level + 1, count, node, visited, idx);
			visited[idx].erase(node);
		}
	}
	return;
}

static void countSawChild(const int n, int level, unsigned long long* count, Vec2<int> pos,
	std::vector<std::unordered_set<Vec2<int>, HashVec2i>>& visited, const unsigned int idx)
{
	countSawChildRec(n, level, count, pos, visited, idx);
	std::lock_guard<std::mutex> locker{ mtx };
	threadFlags &= ~(1 << idx);
	cond.notify_one();
}

static void countSawParentRec(const int n, int level, unsigned long long* count, Vec2<int>& pos,
	std::vector<std::unordered_set<Vec2<int>, HashVec2i>>& visited)
{
	int dist{ uniquePointsDistance(pos, n) };

	if (level == n)
	{
		// subtract (pos.y == 0) since bottom row of unique triangle is missing first entry
		if (dist == 0)
			++count[triangleNumber((n / 2) - pos.y) - (pos.y == 0 && n % 2 == 0) + (pos.x - pos.y) / 2];
		return;
	}

	if (dist > n - level)
		return;

	unsigned int len{ DIRECTIONS.size() };
	for (unsigned int i{ 0 }; i < len; ++i)
	{
		Vec2<int> node{ pos + DIRECTIONS[i] };
		if (visited[0].find(node) == visited[0].end())
		{
			visited[0].insert(node);
			if ((i != len - 1) && (threadFlags != threadsFull))
			{
				for (int j{ 1 }; j < threadCount; ++j) // start at j=1 since parent thread has j=0
				{
					if (!(threadFlags & (1 << j)))
					{
						threadFlags |= (1 << j);
						visited[j] = visited[0]; // initially visited is the same as parent's
						std::thread t{ countSawChild, n, level + 1, count, node, std::ref(visited), j };
						t.detach();
						break;
					}
				}
			}
			else
			{
				countSawParentRec(n, level + 1, count, node, visited);
			}
			visited[0].erase(node);
		}
	}
}

std::vector<unsigned long long> countSaw(int n)
{
	int len{ uniquePoints(n) };

	unsigned long long* count{ new unsigned long long[len * threadCount] {} };
	Vec2<int> pos{ 0, 0 };
	std::vector<std::unordered_set<Vec2<int>, HashVec2i>> visited(threadCount);
	visited[0].insert(pos);
	countSawParentRec(n, 0, count, pos, visited);

	std::unique_lock<std::mutex> locker{ mtx };
	cond.wait(locker, []() { return threadFlags == 1; }); // threadFlags == 1 if only parent thread is left

	std::vector<unsigned long long> result(len);
	for (int j{ 0 }; j < threadCount; ++j)
		for (int i{ 0 }; i < len; ++i)
			result[i] += count[i + len * j];
	delete[] count;

	return result;
}

std::unordered_set<Vec2<int>, HashVec2i> getGrid(int n)
{
	std::unordered_set<Vec2<int>, HashVec2i> grid;
	if (n == 0)
	{
		grid.insert(Vec2<int>{0, 0});
		return grid;
	}
	if (n == 1)
	{
		grid.insert(Vec2<int>{-1, 0});
		grid.insert(Vec2<int>{0, 0});
		grid.insert(Vec2<int>{1, 0});
		return grid;
	}
	grid = getGrid(n - 1);

	if (n % 2 == 1)
	{
		grid.insert(Vec2<int>{0, n / 2});
		grid.insert(Vec2<int>{0, -n / 2});
	}

	auto gridCopy{ grid };
	for (const auto& node : grid)
	{
		Vec2<int> right{ node + Vec2<int>{1, 0} };
		Vec2<int> left{ node + Vec2<int>{-1, 0} };
		if (gridCopy.find(right) == gridCopy.end())
			gridCopy.insert(right);
		if (gridCopy.find(left) == gridCopy.end())
			gridCopy.insert(left);
	}
	return gridCopy;
}

void printSequenceDifference(std::vector<int>& v)
{
	int loopCount{ (int)v.size() - 1 };
	for (int i{ 0 }; i < loopCount; ++i)
	{
		for (int n : v)
			std::cout << n << " ";
		std::cout << '\n';
		std::adjacent_difference(v.begin(), v.end(), v.begin()), v.end();
		v.erase(v.begin());
	}
}

void printPolynomial(int degree)
{
	for (int i{ degree }; i >= 0; --i)
	{
		std::cout << "x" << (degree - i + 1) << "*x^" << i;
		if (i != 0)
			std::cout << " + ";
	}
}
