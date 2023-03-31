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

void PolygonCollider::Draw()
{
	// currentPos - blue
	DrawCircleAtPosition(SDL_Color{ 0, 0, 255, 255 }, position, 5);

	SDL_Point* sdlPoints = new SDL_Point[num_points];
	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x = this->points[i].x;
		sdlPoints[i].y = this->points[i].y;
	}

	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x += position.x;
		sdlPoints[i].y += position.y;

		// other point are red
		DrawCircleAtPosition(SDL_Color{ 255, 0, 0, 255 },  Vector2(sdlPoints[i].x, sdlPoints[i].y), 5);
	}

	// first point - yellow
	DrawCircleAtPosition(SDL_Color{ 255, 255, 0, 255 }, Vector2(sdlPoints[0].x, sdlPoints[0].y), 5);

	// last point - white
	DrawCircleAtPosition(SDL_Color{ 255, 255, 255, 255 }, Vector2(sdlPoints[num_points - 1].x, sdlPoints[num_points - 1].y), 5);

	// i want the rest of the points to be green
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLines(SDLManager::GetRenderer(), sdlPoints, num_points);

	// draw a line form the last point to the first point
	SDL_RenderDrawLine(SDLManager::GetRenderer(), sdlPoints[0].x, sdlPoints[0].y, sdlPoints[num_points - 1].x, sdlPoints[num_points - 1].y);
}

Vector2 PolygonCollider::GetCentre()
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
