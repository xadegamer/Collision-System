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
		Vector2 minimumTranslationVector = Vector2 (colA->GetCollision().GetMinimumTranslationVector().GetX(), colA->GetCollision().GetMinimumTranslationVector().GetY());
		colA->GetOwnerAs<GameObject>()->GetTransform()->SetPosition(colA->GetOwnerAs<GameObject>()->GetTransform()->GetPosition() - (minimumTranslationVector * colA->GetCollision().GetImpulse()));
	}

	if (!colB->IsStatic())
	{
		Vector2 minimumTranslationVector = Vector2(colB->GetCollision().GetMinimumTranslationVector().GetX(), colB->GetCollision().GetMinimumTranslationVector().GetY());
		colB->GetOwnerAs<GameObject>()->GetTransform()->SetPosition(colB->GetOwnerAs<GameObject>()->GetTransform()->GetPosition() - (minimumTranslationVector * colB->GetCollision().GetImpulse()));
	}
}
