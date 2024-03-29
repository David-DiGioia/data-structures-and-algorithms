#include "PathFinding.h"
#include <queue>

bool floodFillCanReach(const Vec2<int>& start, const Vec2<int>& end, int length,
	const std::unordered_set<Vec2<int>, HashVec2i>& grid, const std::unordered_set<Vec2<int>, HashVec2i>& visited)
{
	if (start == end)
		return true;

	std::queue<Vec2<int>> frontier;
	std::unordered_set<Vec2<int>, HashVec2i> visitedNew;
	frontier.push(start);
	visitedNew.insert(start);

	while (!frontier.empty() && length-- >= 1)
	{
		unsigned long long len{ frontier.size() };
		for (unsigned long long i{ 0 }; i < len; ++i)
		{
			Vec2<int> node{ frontier.front() };
			frontier.pop();

			for (const auto& dir : DIRECTIONS)
			{
				Vec2<int> next{ node + dir };
				if (next == end)
					return true;
				if (grid.find(next) != grid.end() && visited.find(next) == visited.end() && visitedNew.find(next) == visitedNew.end())
				{
					frontier.push(next);
					visitedNew.insert(next);
				}
			}
		}
	}
	return false;
}
