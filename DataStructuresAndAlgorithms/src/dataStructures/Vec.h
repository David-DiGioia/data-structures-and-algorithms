#pragma once
#include <functional>
#include <iostream>
#include <array>

template<class T>
struct Vec2
{
	T x;
	T y;
};

// Hash functor for Vec2<int>
struct HashVec2i
{
	std::hash<long long> hash;
	size_t operator()(const Vec2<int>& v) const;
};

template<class T>
Vec2<T> operator+(const Vec2<T>& v1, const Vec2<T>& v2)
{
	return Vec2<T>{ v1.x + v2.x, v1.y + v2.y };
}

template<class T>
Vec2<T> operator-(const Vec2<T> & v)
{
	return Vec2<T>{ -v.x, -v.y };
}

template<class T>
Vec2<T> operator-(const Vec2<T> & v1, const Vec2<T> & v2)
{
	return v1 + (-v2);
}

template<class T>
bool operator==(const Vec2<T> & v1, const Vec2<T> & v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

template<class T>
bool operator!=(const Vec2<T> & v1, const Vec2<T> & v2)
{
	return !(v1 == v2);
}

template<class T>
bool operator<(const Vec2<T> & v1, const Vec2<T> & v2)
{
	if (v1.x == v2.x)
		return v1.y < v2.y;
	else
		return v1.x < v2.x;
}

template<class T>
std::ostream& operator<<(std::ostream& out, Vec2<T> v)
{
	return out << "(" << v.x << ", " << v.y << ")";

}
// Up, down, right, left
constexpr std::array<Vec2<int>, 4> DIRECTIONS{ Vec2<int>{0, 1}, Vec2<int>{0, -1}, Vec2<int>{1, 0}, Vec2<int>{-1, 0} };
