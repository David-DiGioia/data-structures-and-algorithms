#pragma once

template<class T>
struct Vec2
{
	T x;
	T y;
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
