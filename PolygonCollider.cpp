#include "PolygonCollider.h"

void PolygonCollider::SetUp(Transform* owner, SDL_Point* points, float sizeMutiplier, bool isStatic)
{
	Collider::SetUp(owner, Vector2(0, 0), isStatic);
	polygon = new Polygon();
	polygon->points = points;
}

void PolygonCollider::Update()
{
	polygon->position.x = owner->GetPosition().x;
	polygon->position.y = owner->GetPosition().y;
}

void PolygonCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLines(SDLManager::GetRenderer(), polygon->points, polygon->num_points);
}
