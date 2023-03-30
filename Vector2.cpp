#include "Vector2.h"
#include <cmath>


Vector2::Vector2(): x(0), y(0)
{
}


Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(const Vector2& v): x(v.x), y(v.y)
{
}

Vector2 Vector2::operator/(float f) const
{
	return Vector2(x / f, y / f);
}

Vector2& Vector2::operator/=(float f)
{
	x /= f;
	y /= f;
	return *this;
}

Vector2& Vector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-()
{
	return Vector2{ -x, -y };
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2& Vector2::operator*(float scaler)
{
	x *= scaler;
	y *= scaler;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return Vector2{ x, y };
}

bool   Vector2::operator==(const Vector2& v) const
{
	if (this->x == v.x && this->y == v.y)
		return true;
	return false;
}

bool Vector2::operator<(const Vector2& other) const
{
	if (x == other.x) {
		return y < other.y;
	}
	else {
		return x < other.x;
	}
}

float Vector2::dist(const Vector2& v) const
{
	return static_cast<float>(std::sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
}

Vector2 Vector2::normalize()
{
	float length = dist(Vector2(0, 0));
	x /= length;
	y /= length;
	return *this;
}

Vector2 Vector2::Normalized() const
{
	float mag = Magnitude();
	if (mag != 0.0f) {
		return Vector2(x / mag, y / mag);
	}
	// Return a zero vector if the magnitude is 0
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::Lerp(Vector2 v1, Vector2 v2, float t)
{
	return Vector2(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t);
}

Vector2 Vector2::Normalize(Vector2 v)
{
	float length = v.dist(Vector2(0, 0));
	return Vector2(v.x / length, v.y / length);
}

float Vector2::Distance(Vector2 v1, Vector2 v2)
{
	return static_cast<float>(std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y)));
}

float Vector2::Dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}

float Vector2::Length() const
{
	return static_cast<float>(std::sqrt(x * x + y * y));
}

float Vector2::Magnitude() const
{
	return static_cast<float>(std::sqrt(x * x + y * y));
}

Vector2 Vector2::operator*(float f) const
{
	return Vector2(x * f, y * f);
}

Vector2& Vector2::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

Vector2 operator*(float f, const Vector2& v)
{
	return Vector2(v.x * f, v.y * f);
}

Vector2 operator+(const Vector2& lv, const Vector2& rv)
{
	Vector2 v(lv);
	v += rv;
	return v;
}

Vector2 operator-(const Vector2& lv, const Vector2& rv)
{
	Vector2 v(lv);
	v -= rv;
	return v;
}

std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
	out << "(" << v.x << ", " << v.y << ")";
	return out;
}