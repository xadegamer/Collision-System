#include "CircleCollider.h"

void CircleCollider::SetUp(void* owner, Vector2 nextPosition, float _radius, float radiousMutiplier , bool isStatic)
{
	Collider::SetUp(owner, nextPosition, isStatic);
	radius = _radius * radiousMutiplier;
}

void CircleCollider::UpdatePosition(Vector2 nextPosition)
{
	Vector2 currentPosition = Vector2(nextPosition.x + radius, nextPosition.y + radius);
	position = currentPosition;
}

void CircleCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);

	Vector2 centre = GetCentre();
	
	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * 3.14 / 180);
		float y = radius * sin(i * 3.14 / 180);

		SDL_RenderDrawPoint(SDLManager::GetRenderer(), (centre.x + x), (centre.y + y));
	}
}

Vector2 CircleCollider::GetCentre()
{
	return position;
}
