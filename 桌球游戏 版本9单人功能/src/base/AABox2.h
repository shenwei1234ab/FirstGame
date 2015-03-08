#pragma once

#include "Vector2.h"

struct AABox2 {
	union {
		struct {
			Vector2 min_corner, max_corner;
		};
		float _[4];
	};

	AABox2() : min_corner(), max_corner() {}
	AABox2(const Vector2 &_min, const Vector2 &_max) : min_corner(_min), max_corner(_max) {}
	AABox2(float left, float top, float right, float bottom) : min_corner(left, top), max_corner(right, bottom) {}
	AABox2(float *v) : min_corner(v[0], v[1]), max_corner(v[2], v[3]) {}


	AABox2 operator /(const Vector2 &rhs) const {
		return AABox2(min_corner / rhs, max_corner / rhs);
	}

	const Vector2 & corner_0() const {
		return min_corner;
	}

	Vector2 corner_1() const {
		return Vector2(max_corner.x, min_corner.y);
	}

	const Vector2 & corner_2() const {
		return max_corner;
	}

	Vector2 corner_3() const {
		return Vector2(min_corner.x, max_corner.y);
	}
};