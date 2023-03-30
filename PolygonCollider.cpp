#include "PolygonCollider.h"

void PolygonCollider::SetUp(Transform* owner, std::vector<Vector2> _points, bool isStatic)
{
	Collider::SetUp(owner, isStatic);
	points = _points;
	num_points = points.size();
}

void PolygonCollider::Update()
{
	position.x = owner->GetPosition().x;
	position.y = owner->GetPosition().y;
}

void PolygonCollider::Draw()
{
	SDL_Point* sdlPoints = new SDL_Point[num_points];
	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x = this->points[i].x;
		sdlPoints[i].y = this->points[i].y;
	}
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);

	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x += position.x;
		sdlPoints[i].y += position.y;
	}

	// i want the first point to be red
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawPoint(SDLManager::GetRenderer(), sdlPoints[0].x, sdlPoints[0].y);

	// i want the last point to be blue
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawPoint(SDLManager::GetRenderer(), sdlPoints[num_points - 1].x, sdlPoints[num_points - 1].y);

	// i want the rest of the points to be green
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLines(SDLManager::GetRenderer(), sdlPoints, num_points);

	// draw a line form the last point to the first point
	SDL_RenderDrawLine(SDLManager::GetRenderer(), sdlPoints[0].x, sdlPoints[0].y, sdlPoints[num_points - 1].x, sdlPoints[num_points - 1].y);
}

Vector2 PolygonCollider::GetCentre()
{
	return Vector2();
}
