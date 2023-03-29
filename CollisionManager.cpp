 #include "CollisionManager.h"

const static int s_buffer = 4;

bool CollisionManager::DoBoxToBoxCollisionCheck(SDL_Rect* A, SDL_Rect* B, int buffer = 2)
{
	if (A->x + A->w - buffer > B->x && A->x + buffer < B->x + B->w && A->y + A->h - buffer > B->y && A->y + buffer < B->y + B->h)
	{
		return true;
	}
	return false;
}

bool CollisionManager::DoCircleToCircleCollsionCheck(SDL_Rect* a, float radiousA, SDL_Rect* b, float radiousB)
{
	float totalRadiusSquared = radiousA + radiousB;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	Vector2 circleCentreA = Vector2(a->x + a->w / 2, a->y + a->h / 2);

	Vector2 circleCentreB = Vector2(b->x + b->w / 2, b->y + b->h / 2);
	// if the distance between the centers of the circles is less than the sum of their radii
	if (DistanceSquared(circleCentreA.x, circleCentreA.y, circleCentreB.x, circleCentreB.y) < totalRadiusSquared)
	{
		// the circles have collided
		return true;
	}
	
	// otherwise the circles have not collided
	return false;
}

bool CollisionManager::DoBoxToCircleCollsionCheck(SDL_Rect* box, SDL_Rect* circle, float radious)
{
	//Closest point on collision box
	int cX, cY;

	Vector2 circleCentre = Vector2(circle->x + circle->w / 2, circle->y + circle->h / 2);

	Vector2 boxCentre = Vector2(box->x + box->w / 2, box->y + box->h / 2);

	//Find closest x offset
	if (circleCentre.x < box->x)
	{
		cX = box->x;
	}
	else if (circleCentre.x > box->x + box->w)
	{
		cX = box->x + box->w;
	}
	else
	{
		cX = circleCentre.x;
	}
	
	//Find closest y offset
	
	if (circleCentre.y < box->y)
	{
		cY = box->y;
	}
	else if (circleCentre.y > box->y + box->h)
	{
		cY = box->y + box->h;
	}
	else
	{
		cY = circleCentre.y;
	}
	
	//If the closest point is inside the circle
	
	if (DistanceSquared(circleCentre.x, circleCentre.y, cX, cY) < radious * radious)
	{
		//This box and the circle have collided
		return true;
	}
	
	//If the shapes have not collided
	
	return false;
}

bool CollisionManager::CheckCollision(Collider* colA, Collider* colB)
{
	BoxCollider* boxA = dynamic_cast<BoxCollider*>(colA);
	BoxCollider* boxB = dynamic_cast<BoxCollider*>(colB);

	CircleCollider* circleA = dynamic_cast<CircleCollider*>(colA);
	CircleCollider* circleB = dynamic_cast<CircleCollider*>(colB);

	if (boxA != nullptr && boxB != nullptr)
	{
		return DoBoxToBoxCollisionCheck(boxA->GetColliderRect(), boxB->GetColliderRect(), s_buffer);
	}
	else if (circleA != nullptr && circleB != nullptr)
	{
		return DoCircleToCircleCollsionCheck(circleA->GetColliderRect(), circleA->GetRadius(), circleB->GetColliderRect(), circleB->GetRadius());
	}
	else if (boxA != nullptr && circleB != nullptr)
	{
		return DoBoxToCircleCollsionCheck(boxA->GetColliderRect(), circleB->GetColliderRect(), circleB->GetRadius());
	}
	else if (circleA != nullptr && boxB != nullptr)
	{
		return DoBoxToCircleCollsionCheck(boxB->GetColliderRect(), circleA->GetColliderRect(), circleA->GetRadius());
	}
}

double CollisionManager::DistanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

void CollisionManager::HandleAllCollision()
{
	//check collision between all game objects with colliders
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* colliderA = nullptr;
		if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed() && GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(colliderA))
		{
			for (int j = 0; j < GameObject::GetActiveGameobjects().size(); j++)
			{
				Collider* colliderB = nullptr;
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed() && GameObject::GetActiveGameobjects()[j]->TryGetComponent<Collider>(colliderB))
				{
					if (colliderA != colliderB && colliderA->GetIsEnabled() && colliderB->GetIsEnabled())
					{
						if (CollisionManager::CheckCollision(colliderA, colliderB))
						{
							colliderA->OnCollision(colliderB);
							colliderB->OnCollision(colliderA);
						}
					}
				}
			}
		}
	}
}

