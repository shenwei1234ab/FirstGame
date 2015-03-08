#pragma once
#include "stdafx.h"



struct Vector2 
{
	union 
	{
		struct 
		{
			float x, y;
		};
		float _[2];
	};

	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(float *v) : x(v[0]), y(v[1]) {}

	static Vector2 Zero() 
	{
		return Vector2();
	}

	Vector2 operator +() const {
		return *this;
	}

	Vector2 operator -() const {
		return Vector2(-x, -y);
	}

	Vector2 operator +(const Vector2 &rhs) const {
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator -(const Vector2 &rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator *(const Vector2 &rhs) const {
		return Vector2(x * rhs.x, y * rhs.y);
	}

	Vector2 operator /(const Vector2 &rhs) const {
		return Vector2(x / rhs.x, y / rhs.y);
	}

	Vector2 operator *(float s) const {
		return Vector2(x * s, y * s);
	}

	Vector2 operator /(float s) const {
		return Vector2(x / s, y / s);
	}

	Vector2 & operator =(const Vector2 &rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	Vector2 & operator +=(const Vector2 &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 & operator -=(const Vector2 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 & operator *=(const Vector2 &rhs) {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vector2 & operator /=(const Vector2 &rhs) {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vector2 & operator *=(float s) {
		x *= s;
		y *= s;
		return *this;
	}

	Vector2 & operator /=(float s) {
		x /= s;
		y /= s;
		return *this;
	}

	//bool operator ==(const Vector2 &rhs) const 
	//{
	//	if(  fabs(x-rhs.x)<= ELIPSE  && fabs(y-rhs.y )<=ELIPSE)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	bool operator ==(const Vector2 &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator !=(const Vector2 &rhs) const {
		return !((*this)==rhs);
	}

	bool operator >=(const Vector2 &rhs) const {
		return x >= rhs.x && y >= rhs.y;
	}

	bool operator <(const Vector2 &rhs) const {
		return x < rhs.x && y < rhs.y;
	}
	//µã»ý
	float dot_product(const Vector2 &rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	
	//²î»ý
	float cross_product(const Vector2 &rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	float length_square() const {
		return x * x + y * y;
		// return dot_product(*this);
	}

	float length() const {
		return ::sqrtf(x * x + y * y);
	}

	float normalize() {
		float len = length();
		if (len) {
			x /= len;
			y /= len;
		}
		return len;
	} 


	Vector2 & Unit()
	{
		float len = length();
		if (len) {
			x /= len;
			y /= len;
		}
		return *this;
	}
};

inline Vector2 operator *(float lhs, const Vector2 &rhs) 
{
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}