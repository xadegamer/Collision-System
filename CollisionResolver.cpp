#include "CollisionResolver.h"

#include "CollisionManager.h"

#include "GameObject.h"

void CollisionResolver::Initialize()
{
	CollisionManager<GameObject>::AddListener(CollisionResolver::ResolveCollision);
}

void CollisionResolver::ResolveCollision(Collider<GameObject>* colA, Collider<GameObject>* colB)
{
	if (!colA->IsStatic())
	{
		GameObject* gameObjectA = colA->GetOwner();
		Vector2 minimumTranslationVector = Vector2 (colA->GetCollision().GetMinimumTranslationVector().GetX(), colA->GetCollision().GetMinimumTranslationVector().GetY());
		colA->GetOwner()->GetTransform()->SetPosition(colA->GetOwner()->GetTransform()->GetPosition() - (minimumTranslationVector * colA->GetCollision().GetImpulse()));
	}

	if (!colB->IsStatic())
	{
		Vector2 minimumTranslationVector = Vector2(colB->GetCollision().GetMinimumTranslationVector().GetX(), colB->GetCollision().GetMinimumTranslationVector().GetY());
		colB->GetOwner()->GetTransform()->SetPosition(colB->GetOwner()->GetTransform()->GetPosition() - (minimumTranslationVector * colB->GetCollision().GetImpulse()));
	}
}
