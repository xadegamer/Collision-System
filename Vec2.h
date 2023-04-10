#pragma once

#include <ostream>

namespace CollisionSystem
{
	class Vec2
	{
	private:
		float x{ 0 }, y{ 0 };

	public:

		Vec2();
		Vec2(float x, float y);
		Vec2(const Vec2& v);

		float Dist(const Vec2& v) const;

		Vec2 Perpendicular()const;

		Vec2 Normalized() const;

		float Length() const;

		float Magnitude() const;

		static Vec2 Lerp(Vec2 v1, Vec2 v2, float t);

		static Vec2 Normalize(Vec2 v);

		static float Distance(Vec2 v1, Vec2 v2);

		static float Dot(Vec2 v1, Vec2 v2);

		static Vec2 Zero();

		static Vec2 Clamp(Vec2 v, Vec2 min, Vec2 max);

		inline float GetX() const { return x; }

		inline float GetY() const { return y; }

		// operators
		Vec2 operator*(float f) const;

		Vec2& operator*=(float f);

		Vec2 operator/(float f) const;

		Vec2& operator/=(float f);

		Vec2& operator=(const Vec2& v);

		Vec2 operator+(const Vec2& v);

		Vec2 operator-(const Vec2& v);

		Vec2 operator-();

		Vec2& operator+=(const Vec2& v);

		Vec2& operator-=(const Vec2& v);

		Vec2& operator*(const Vec2& v);

		Vec2& operator*(float scaler);

		Vec2 operator/(const Vec2& v);

		bool operator==(const Vec2& v) const;

		bool operator<(const Vec2& other) const;
	};
}

