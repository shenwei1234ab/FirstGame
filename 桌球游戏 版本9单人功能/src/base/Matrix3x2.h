#pragma once

#include "Vector2.h"

//2维变换矩阵
struct Matrix3x2 {
	union {
		struct {
			Vector2 r1, r2, r3;
		};
		struct {
			float m11, m12;
			float m21, m22;
			float m31, m32;
		};
		float m[6];
	};

	enum constructor {
		c_nothing = 0,
		c_identity,
		c_copy,
		c_inverse
	};
	


	Matrix3x2(constructor c = c_identity) {
		switch (c) {
		case c_identity:
		case c_copy:
		case c_inverse:
			make_identity();
			break;
		default:
			break;
		}
	};

	Matrix3x2(const Matrix3x2 &other, constructor c = c_copy) {
		switch (c) {
		case c_identity:
			make_identity();
			break;
		case c_copy:
			for (int i = 0; i < 6; ++i) {
				m[i] = other.m[i];
			}
			break;
		case c_inverse:
			other.inverse(*this);
			break;
		default:
			break;
		}
	}

	Matrix3x2 & make_identity() {
		m11 = 1;
		m12 = 0;
		m21 = 0;
		m22 = 1;
		m31 = 0;
		m32 = 0;
		return *this;
	}
	//矩阵的乘法
	Matrix3x2 & make_product(const Matrix3x2 &lhs, const Matrix3x2 &rhs) {
		m11 = lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21;
		m12 = lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22;

		m21 = lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21;
		m22 = lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22;

		m31 = lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + rhs.m31;
		m32 = lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + rhs.m32;
		return *this;
	};
	//向量与矩阵的乘法
	Vector2 transform_vector(const Vector2 &v) const {
		return Vector2(
			v.x * m11 + v.y * m21 + m31,
			v.x * m12 + v.y * m22 + m32
			);
	}

	Vector2 transform_normal(const Vector2 &n) const {
		return Vector2(
			n.x * m11 + n.y * m21,
			n.x * m12 + n.y * m22
			);
	}

	bool inverse(Matrix3x2 &result) const {
		float d = m11 * m22 - m12 * m21;
		if (d == 0) {
			return false;
		}
		float inv = 1.f / d;
		result.m11 = m22 * inv;
		result.m12 = -m12 * inv;
		result.m21 = -m21 * inv;
		result.m22 = m11 * inv;
		result.m31 = -(m31 * result.m11 + m32 * result.m21);
		result.m32 = -(m32 * result.m12 + m32 * result.m22);
		return true;
	}
};