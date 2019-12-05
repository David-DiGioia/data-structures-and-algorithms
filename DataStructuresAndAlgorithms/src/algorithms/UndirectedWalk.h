#pragma once
#include <vector>
#include <unordered_set>
#include "../dataStructures/Vec.h"

// How many unique points must we count paths to in order to describe all
// self-avoiding walks of length n?
int uniquePoints(int n);

// Minimum path distance between 2 points. In other words, the
// number of steps needed to reach pos2 from pos1
int pathDistance(const Vec2<int>& pos1, const Vec2<int>& pos2);

// Minimum path distance to get from pos to one of the zeros on the right.
int pointsDistance(const Vec2<int>& pos, int n);

// Minimum path distance to get to one of unique points in triangle.
int uniquePointsDistance(const Vec2<int>& pos, int n);

// Grid of possible points a path of length n my reach
std::unordered_set<Vec2<int>, HashVec2i> getGrid(int n);

// Count number of undirected walks. BaseFn decides if that means counting all
// walks ending on y=0 or just certain arbitrary points.
// BaseFn returns true if a base case is reached. TermFn returns true if we should
// terminate the search early. For example, if no paths are possible
std::vector<unsigned long long> countUndirectedWalk(int n);

// Repeatedly take the adjacent difference of a vector, printing at each step.
// This is helpful to tell what degree a polynomial is.
void printSequenceDifference(std::vector<int>& v);

void printPolynomial(int degree);
