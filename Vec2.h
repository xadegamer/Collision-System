#pragma once

#include <ostream>

class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& v);
	virtual ~Vec2() {}

	// basic functions
	float dist(const Vec2& v) const;
	bool empty() { return (x == 0 && y == 0) ? true : false; }

	Vec2 Perpendicular()const;

	Vec2 normalize();

	Vec2 Normalized() const;

	static Vec2 Lerp(Vec2 v1, Vec2 v2, float t);

	static Vec2 Normalize(Vec2 v);

	static float Distance(Vec2 v1, Vec2 v2);

	static float Dot(Vec2 v1, Vec2 v2);

	static Vec2 Zero();

	static Vec2 Clamp(Vec2 v, Vec2 min, Vec2 max);

	float Length() const;

	float Magnitude() const;

	// float * vector functions
	Vec2 operator*(float f) const;
	Vec2& operator*=(float f);

	// vector * float functions
	friend Vec2 operator*(float f, const Vec2& v);

	// vector / float functions
	Vec2 operator/(float f) const;
	Vec2& operator/=(float f);


	// operators
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

	// data - public
	float     x{ 0 }, y{ 0 };
};

// additional operators for arithmetic and stream operations
Vec2 operator+(const Vec2& lv, const Vec2& rv);
Vec2 operator-(const Vec2& lv, const Vec2& rv);
std::ostream& operator<<(std::ostream& out, const Vec2& v);
