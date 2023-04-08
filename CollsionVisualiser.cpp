#include "CollsionVisualiser.h"

#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "GameObject.h"

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

	// draw the lines
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
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

		SDL_Color colliderColour = ((GameObject*)colliderA->GetOwner())->GetColor();

		// try to cast to a circle collider
		CircleCollider* circleCollider = dynamic_cast<CircleCollider*>(colliderA);
		if (circleCollider != nullptr)
		{
			DrawCircleAtPosition(colliderColour, circleCollider->GetCenter(), circleCollider->GetRadius());
			continue;
		}

		// try to cast to a box collider
		BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(colliderA);
		if (boxCollider != nullptr)
		{
			DrawBoxAtPosition(colliderColour, boxCollider->GetPosition(), boxCollider->GetWidth(), boxCollider->GetHeight());
			continue;
		}

		// try to cast to a polygon collider
		PolygonCollider* polygonCollider = dynamic_cast<PolygonCollider*>(colliderA);
		if (polygonCollider != nullptr)
		{
			DrawPolygon(colliderColour, polygonCollider->GetWorldPoints());
			continue;
		}
	}
}
