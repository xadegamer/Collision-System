#include "Direction.h"

#include <stdlib.h>

Vector2 Direction::GetDirection(DirectionType directionType)
{
    switch (directionType)
    {
	case DirectionType::Up:
		return Vector2(0, -1);
		break;
	case DirectionType::UpRight:
		return Vector2(1, -1);
		break;
	case DirectionType::UpLeft:
		return Vector2(-1, -1);
		break;
	case DirectionType::Down:
		return Vector2(0, 1);
		break;
	case DirectionType::DownRight:
		return Vector2(1, 1);
		break;
	case DirectionType::DownLeft:
		return Vector2(-1, 1);
		break;
	case DirectionType::Right:
		return Vector2(1, 0);
		break;
	case DirectionType::Left:
		return Vector2(-1, 0);
		break;
	default:
		break;
	}
}

Vector2 Direction::GetRandomDirection()
{
	return GetDirection((DirectionType)(rand() % 8));
}
