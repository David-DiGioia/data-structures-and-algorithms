#pragma once
#include <functional>

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
	inline size_t operator()(const Vec2<int>& v) const
	{
		long long temp{ ((long long)v.x) ^ (((long long)v.y) << 32) };
		return hash(temp);
	}
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

