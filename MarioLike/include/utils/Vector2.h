#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
struct Vec2
{
	T x;
	T y;

	Vec2()
	{
		x = 0;
		y = 0;
	}

	Vec2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	void Set(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	/*--------------------------------------------*/
	inline bool IsZero() const
	{
		return x == 0 && y == 0;
	}

	/*--------------------------------------------*/
	inline Vec2& Add(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;

		return *this;
	}

	inline Vec2& Substract(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;

		return *this;
	}

	inline Vec2& Multiply(const Vec2& _other)
	{
		x *= _other.x;
		y *= _other.y;

		return *this;
	}

	inline Vec2& Divide(const Vec2& _other)
	{
		x /= _other.x;
		y /= _other.y;

		return *this;
	}

	/*--------------------------------------------*/
	inline friend Vec2 operator+(Vec2 _main, const Vec2& _other)
	{
		return _main.Add(_other);
	}

	inline friend Vec2 operator-(Vec2 _main, const Vec2& _other)
	{
		return _main.Substract(_other);
	}

	inline friend Vec2 operator*(Vec2 _main, const Vec2& _other)
	{
		return _main.Multiply(_other);
	}

	inline friend Vec2 operator/(Vec2 _main, const Vec2& _other)
	{
		return _main.Divide(_other);
	}

	/*--------------------------------------------*/
	inline Vec2& operator+=(const Vec2& _other)
	{
		return Add(_other);
	}

	inline Vec2& operator-=(const Vec2& _other)
	{
		return Substract(_other);
	}

	inline Vec2& operator*=(const Vec2& _other)
	{
		return Multiply(_other);
	}

	inline Vec2& operator/=(const Vec2& _other)
	{
		return Divide(_other);
	}

	/*--------------------------------------------*/
	inline Vec2 operator+(double _value)
	{
		T value = static_cast<T>(_value);

		return Vec2(x + value, y + value);
	}

	inline Vec2 operator-(double _value)
	{
		T value = static_cast<T>(_value);

		return Vec2(x - value, y - value);
	}

	inline Vec2 operator*(double _value)
	{
		T value = static_cast<T>(_value);

		return Vec2(x * value, y * value);
	}

	inline Vec2 operator/(double _value)
	{
		T value = static_cast<T>(_value);

		return Vec2(x / value, y / value);
	}

	/*--------------------------------------------*/
	inline Vec2& operator+=(double _value)
	{
		x += _value;
		y += _value;

		return *this;
	}

	inline Vec2& operator-=(double _value)
	{
		x -= _value;
		y -= _value;

		return *this;
	}

	inline Vec2& operator*=(double _value)
	{
		x *= _value;
		y *= _value;

		return *this;
	}

	inline Vec2& operator/=(double _value)
	{
		x /= _value;
		y /= _value;

		return *this;
	}

	/*--------------------------------------------*/
	inline operator Vec2<float>()
	{
		return { static_cast<float>(x), static_cast<float>(y) };
	}

	inline operator Vec2<double>()
	{
		return { static_cast<double>(x), static_cast<double>(y) };
	}

	inline operator Vec2<int>()
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}

	inline operator Vec2<unsigned int>()
	{
		return { static_cast<unsigned int>(x), static_cast<unsigned int>(y) };
	}

	/*--------------------------------------------*/
	inline bool operator==(const Vec2& _other) const
	{
		return (x == _other.x) && (y == _other.y);
	}

	inline bool operator!=(const Vec2& _other) const
	{
		return (x != _other.x) || (y != _other.y);
	}

	/*--------------------------------------------*/
	inline operator sf::Vector2<T>()
	{
		return { x, y };
	}
};



using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
