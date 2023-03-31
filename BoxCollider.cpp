#include "BoxCollider.h"

void BoxCollider::SetUp(void* owner, Vector2 nextPosition, Vector2 size, bool isStatic)
{
	Collider::SetUp(owner, nextPosition, isStatic);
	width = size.x;
	height = size.y;
}

void BoxCollider::UpdatePosition(Vector2 nextPosition)
{
	position = nextPosition;
}

void BoxCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_Rect visualRect  = { position.x, position.y, width, height };
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &visualRect);
}

Vector2 BoxCollider::GetCentre()
{
	return Vector2(position.x + width / 2, position.y + height / 2);
}

std::vector<Vector2> BoxCollider::GetWorldPoints()
{
	std::vector<Vector2> points;
	points.push_back(Vector2(position.x, position.y));
	points.push_back(Vector2(position.x + width, position.y));
	points.push_back(Vector2(position.x + width, position.y + height));
	points.push_back(Vector2(position.x, position.y + height));
    return points;
}