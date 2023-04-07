#include "CollsionVisualiser.h"

#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"

void CollsionVisualiser::DrawBoxAtPosition(SDL_Color sdlColor, Vector2 position, int width, int height)
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_Rect visualRect = { position.x, position.y, width, height };
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &visualRect);
}

void CollsionVisualiser::DrawCircleAtPosition(SDL_Color sdlColor, Vector2 position, int radius)
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * 3.14 / 180);
		float y = radius * sin(i * 3.14 / 180);
		SDL_RenderDrawPoint(SDLManager::GetRenderer(), (position.x + x), (position.y + y));
	}
}

void CollsionVisualiser::DrawPolygon(SDL_Color sdlColor, std::vector<Vector2> _points)
{
	int num_points = _points.size();

	SDL_Point* sdlPoints = new SDL_Point[num_points];
	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x = _points[i].x;
		sdlPoints[i].y = _points[i].y;
	}

	for (int i = 0; i < num_points; i++)
	{
		DrawCircleAtPosition(SDL_Color{ 255, 0, 0, 255 }, Vector2(sdlPoints[i].x, sdlPoints[i].y), 5);
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

void CollsionVisualiser::DrawAllColliders()
{
	for (int i = 0; i < Collider::GetAllColliders().size(); i++)
	{
		Collider* colliderA = Collider::GetAllColliders()[i];

		if (!colliderA->GetIsEnabled()) continue;

		// try to cast to a circle collider
		CircleCollider* circleCollider = dynamic_cast<CircleCollider*>(colliderA);
		if (circleCollider != nullptr)
		{
			DrawCircleAtPosition(SDL_Color{ 0, 255, 0, 255 }, circleCollider->GetCenter(), circleCollider->GetRadius());
			continue;
		}

		// try to cast to a box collider
		BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(colliderA);
		if (boxCollider != nullptr)
		{
			DrawBoxAtPosition(SDL_Color{ 0, 255, 0, 255 }, boxCollider->GetPosition(), boxCollider->GetWidth(), boxCollider->GetHeight());
			DrawPolygon(SDL_Color{ 0, 255, 0, 255 }, boxCollider->GetWorldPoints());
			continue;
		}

		// try to cast to a polygon collider
		PolygonCollider* polygonCollider = dynamic_cast<PolygonCollider*>(colliderA);
		if (polygonCollider != nullptr)
		{
			DrawPolygon(SDL_Color{ 0, 255, 0, 255 }, polygonCollider->GetWorldPoints());
			continue;
		}
	}
}
