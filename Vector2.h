#pragma once

#include <ostream>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
	virtual ~Vector2() {}

	// basic functions
	float dist(const Vector2& v) const;
	bool empty() { return (x == 0 && y == 0) ? true : false; }

	Vector2 Perpendicular()const;

	Vector2 normalize();

	Vector2 Normalized() const;

	static Vector2 Lerp(Vector2 v1, Vector2 v2, float t);

	static Vector2 Normalize(Vector2 v);

	static float Distance(Vector2 v1, Vector2 v2);

	static float Dot(Vector2 v1, Vector2 v2);

	static Vector2 Zero();

	static Vector2 Clamp (Vector2 v, Vector2 min, Vector2 max);

	float Length() const;

	float Magnitude() const;

	// float * vector functions
	Vector2 operator*(float f) const;
	Vector2& operator*=(float f);

	// vector * float functions
	friend Vector2 operator*(float f, const Vector2& v);
	
	// vector / float functions
	Vector2 operator/(float f) const;
	Vector2& operator/=(float f);
	

	// operators
	Vector2& operator=(const Vector2& v);
	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator-();
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);

	Vector2& operator*(const Vector2& v);
	Vector2& operator*(float scaler);

	Vector2 operator/(const Vector2& v);
	
	bool operator==(const Vector2& v) const;

	bool operator<(const Vector2& other) const;

	// data - public
	float     x{ 0 }, y{ 0 };
};

// additional operators for arithmetic and stream operations
Vector2 operator+(const Vector2& lv, const Vector2& rv);
Vector2 operator-(const Vector2& lv, const Vector2& rv);
std::ostream& operator<<(std::ostream& out, const Vector2& v);
