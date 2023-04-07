#include "CollisionResolver.h"

#include "CollisionManager.h"

void CollisionResolver::Initialize()
{
	CollisionManager::OnAnyCollisionEvent = ResolveCollision;
}

void CollisionResolver::Shutdown()
{
	CollisionManager::OnAnyCollisionEvent = nullptr;
}

void CollisionResolver::ResolveCollision(Collider* colA, Collider* colB)
{
	GameObject* gameObjectA = (GameObject*)colA->GetOwner();
	gameObjectA->GetTransform()->SetPosition(gameObjectA->GetTransform()->GetPosition() - (colA->GetCollision().GetMinimumTranslationVector() * colA->GetCollision().GetImpulse()));

	GameObject* gameObjectB = (GameObject*)colB->GetOwner();
	gameObjectB->GetTransform()->SetPosition(gameObjectB->GetTransform()->GetPosition() - (colB->GetCollision().GetMinimumTranslationVector() * colB->GetCollision().GetImpulse()));
}
