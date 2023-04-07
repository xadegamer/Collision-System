#include "CollisionResolver.h"

#include "CollisionManager.h"

void CollisionResolver::Initialize()
{
	CollisionManager::OnAnyCollisionEvent = std::bind(&CollisionResolver::ResolveCollision, std::placeholders::_1);
}

void CollisionResolver::Shutdown()
{
	CollisionManager::OnAnyCollisionEvent = nullptr;
}

void CollisionResolver::ResolveCollision(std::vector<Collision> collisions)
{
	for (size_t i = 0; i < collisions.size(); i++)
	{
		GameObject* collided = (GameObject*)collisions[i].GetColliderHit()->GetOwner();
		collided->GetTransform()->SetPosition(collided->GetTransform()->GetPosition() + (collisions[i].GetMinimumTranslationVector() * collisions[i].GetImpulse()));
	}
}
