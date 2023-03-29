#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Translate(Vector2 translation)
{
	position += translation;
}

void Transform::TranslateX(float x)
{
	position.x += x;
}

void Transform::TranslateY(float y)
{
	position.y += y;
}

Vector2 Transform::GetForward()
{
	return Vector2::Normalize(position);
}

Vector2 Transform::GetRight()
{
	return Vector2::Normalize(Vector2(position.y, -position.x));
}
