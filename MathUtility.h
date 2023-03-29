#pragma once
#include <iostream>
#include "InputManager.h"

using namespace std;

#define PI 3.14159265358979323846

class MathUtility
{
public:
	
	static float GetAngleFromTraget(Vector2 position, Vector2 target, float width, float height)
	{
		float x = target.x - (position.x + width / 2);
		float y = target.y - (position.y + height / 2);
		return 90 + atan2(y, x) * 180 / PI;
	}

	static Vector2 GetDirectionToTarget(Vector2 position, Vector2 target)
	{
		float x = target.x - position.x;
		float y = target.y - position.y;
		return Vector2(x, y).normalize();
	}

	static float GetAngleFromMouse(Vector2 position, float width, float height)
	{
		return GetAngleFromTraget(position, InputManager::GetMousePosition(), width, height);
	}

	static Vector2 GetDirectionToMouse(Vector2 position)
	{
		return GetDirectionToTarget(position, InputManager::GetMousePosition());
	}

	static float Clamp(float value, float min, float max)
	{
		if (value < min) return min; else if (value > max)return max; else return value;
	}

	static bool IsPointInRect(Vector2 point, Vector2 rectPos, Vector2 rectSize)
	{
		return point.x > rectPos.x && point.x < rectPos.x + rectSize.x && point.y > rectPos.y && point.y < rectPos.y + rectSize.y;
	}

	static int RandomRange(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	static float DistanceBetweenTwoPoints(Vector2 point1, Vector2 point2)
	{
		float x = point1.x - point2.x;
		float y = point1.y - point2.y;
		return sqrt(x * x + y * y);
	}

	static Vector2 RandomPositionAroundRange(Vector2 position, int range)
	{
		int x = RandomRange(position.x - range, position.x + range);
		int y = RandomRange(position.y - range, position.y + range);
		return Vector2(x, y);
	}
};