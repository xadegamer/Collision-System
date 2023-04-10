#include "CollisionResolver.h"

#include "CollisionManager.h"

#include "GameObject.h"

void CollisionResolver::Initialize()
{
	CollisionManager::AddListener(CollisionResolver::ResolveCollision);
}

void CollisionResolver::ResolveCollision(Collider* colA, Collider* colB)
{
	if (!colA->IsStatic())
	{
		GameObject* gameObjectA = (GameObject*)colA->GetOwner();
		gameObjectA->GetTransform()->SetPosition(gameObjectA->GetTransform()->GetPosition() - (colA->GetCollision().GetMinimumTranslationVector() * colA->GetCollision().GetImpulse()));
	}

	if (!colB->IsStatic())
	{
		GameObject* gameObjectB = (GameObject*)colB->GetOwner();
		gameObjectB->GetTransform()->SetPosition(gameObjectB->GetTransform()->GetPosition() - (colB->GetCollision().GetMinimumTranslationVector() * colB->GetCollision().GetImpulse()));
	}
}
