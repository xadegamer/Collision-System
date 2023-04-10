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
		Vector2 minimumTranslationVector = Vector2 (colA->GetCollision().GetMinimumTranslationVector().GetX(), colA->GetCollision().GetMinimumTranslationVector().GetY());
		gameObjectA->GetTransform()->SetPosition(gameObjectA->GetTransform()->GetPosition() - (minimumTranslationVector * colA->GetCollision().GetImpulse()));
	}

	if (!colB->IsStatic())
	{
		GameObject* gameObjectB = (GameObject*)colB->GetOwner();
		Vector2 minimumTranslationVector = Vector2(colB->GetCollision().GetMinimumTranslationVector().GetX(), colB->GetCollision().GetMinimumTranslationVector().GetY());
		gameObjectB->GetTransform()->SetPosition(gameObjectB->GetTransform()->GetPosition() - (minimumTranslationVector * colB->GetCollision().GetImpulse()));
	}
}
