#include "BoxCollider.h"

void BoxCollider::SetUp(Transform* owner, Vector2 size, bool isStatic)
{
	Collider::SetUp(owner, isStatic);

	width = size.x;
	height = size.y;

	position.x = owner->GetPosition().x;
	position.y = owner->GetPosition().y;
}

void BoxCollider::Update()
{
	position.x = owner->GetPosition().x;
	position.y = owner->GetPosition().y;
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
