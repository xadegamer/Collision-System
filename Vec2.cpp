#include "Vec2.h"
#include <cmath>

namespace CollisionSystem
{
	Vec2::Vec2() : x(0), y(0)
	{
	}


	Vec2::Vec2(float x, float y) : x(x), y(y)
	{
	}

	Vec2& Vec2::operator/=(float f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	Vec2& Vec2::operator=(const Vec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vec2 Vec2::operator+(const Vec2& v)
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 Vec2::operator-(const Vec2& v)
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 Vec2::operator-()
	{
		return Vec2{ -x, -y };
	}

	Vec2& Vec2::operator+=(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2& Vec2::operator*(const Vec2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vec2& Vec2::operator*(float scaler)
	{
		x *= scaler;
		y *= scaler;
		return *this;
	}

	Vec2 Vec2::operator/(const Vec2& v)
	{
		x /= v.x;
		y /= v.y;
		return Vec2{ x, y };
	}

	bool   Vec2::operator==(const Vec2& v) const
	{
		if (this->x == v.x && this->y == v.y)
			return true;
		return false;
	}

	bool Vec2::operator<(const Vec2& other) const
	{
		if (x == other.x) {
			return y < other.y;
		}
		else {
			return x < other.x;
		}
	}

	float Vec2::Dist(const Vec2& v) const
	{
		return static_cast<float>(std::sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
	}

	Vec2 Vec2::Perpendicular()const
	{
		return Vec2(-y, x);
	}

	Vec2 Vec2::Normalized() const
	{
		float mag = Magnitude();
		if (mag != 0.0f) {
			return Vec2(x / mag, y / mag);
		}
		// Return a zero vector if the magnitude is 0
		return Vec2(0.0f, 0.0f);
	}

	Vec2 Vec2::Normalize(Vec2 v)
	{
		float length = v.Dist(Vec2(0, 0));
		return Vec2(v.x / length, v.y / length);
	}

	float Vec2::Distance(Vec2 v1, Vec2 v2)
	{
		return static_cast<float>(std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y)));
	}

	float Vec2::Dot(Vec2 v1, Vec2 v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	Vec2 Vec2::Zero()
	{
		return Vec2(0, 0);
	}

	float Vec2::Length() const
	{
		return static_cast<float>(std::sqrt(x * x + y * y));
	}

	float Vec2::Magnitude() const
	{
		return static_cast<float>(std::sqrt(x * x + y * y));
	}

	Vec2 operator*(float f, const Vec2& v)
	{
		return Vec2(v.GetX() * f, v.GetY() * f);
	}

	Vec2 operator+(const Vec2& lv, const Vec2& rv)
	{
		Vec2 v(lv);
		v += rv;
		return v;
	}

	Vec2 operator-(const Vec2& lv, const Vec2& rv)
	{
		Vec2 v(lv);
		v -= rv;
		return v;
	}

	std::ostream& operator<<(std::ostream& out, const Vec2& v)
	{
		out << "(" << v.GetX() << ", " << v.GetY() << ")";
		return out;
	}
}