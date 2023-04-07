#include "PolygonCollider.h"

void PolygonCollider::SetUp(void* owner, Vector2 nextPosition, std::vector<Vector2> _points, bool isStatic)
{
	Collider::SetUp(owner, nextPosition, isStatic);
	points = _points;
	num_points = points.size();
}

void PolygonCollider::UpdatePosition(Vector2 nextPosition)
{
	position = nextPosition;
}

Vector2 PolygonCollider::GetCenter()
{
	return position;
}


std::vector<Vector2> PolygonCollider::GetWorldPoints()
{
	std::vector<Vector2> worldPoints;
	for (int i = 0; i < num_points; i++)
	{
		worldPoints.push_back(Vector2(points[i].x + position.x, points[i].y + position.y));
	}
	return worldPoints;
}

void PolygonCollider::DrawCircleAtPosition(SDL_Color sdlColor, Vector2 position, int radius)
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * 3.14 / 180);
		float y = radius * sin(i * 3.14 / 180);
		SDL_RenderDrawPoint(SDLManager::GetRenderer(), (position.x + x), (position.y + y));
	}
}
