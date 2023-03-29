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

bool CollisionManager::DoPolygonToPolygonCollisionCheck(Polygon* A, Polygon* B, int buffer)
{
	// Loop through each edge in both polygons
	for (int i = 0; i < A->num_points; i++) {
		Vector2 point1 = { A->points[i].x + A->position.x, A->points[i].y + A->position.y };
		Vector2 point2 = { A->points[(i + 1) % A->num_points].x + A->position.x, A->points[(i + 1) % A->num_points].y + A->position.y };
		Vector2 edge = { point2.x - point1.x, point2.y - point1.y };
		Vector2 normal = { -edge.y, edge.x };
		float len = sqrt(normal.x * normal.x + normal.y * normal.y);
		normal.x /= len;
		normal.y /= len;

		// Project each point in both polygons onto the normal of the current edge
		float minA = INFINITY, maxA = -INFINITY;
		for (int j = 0; j < A->num_points; j++) {
			Vector2 p = { A->points[j].x + A->position.x, A->points[j].y + A->position.y };
			float proj = p.x * normal.x + p.y * normal.y;
			if (proj < minA) {
				minA = proj;
			}
			if (proj > maxA) {
				maxA = proj;
			}
		}

		float minB = INFINITY, maxB = -INFINITY;
		for (int j = 0; j < B->num_points; j++) {
			Vector2 p = { B->points[j].x + B->position.x, B->points[j].y + B->position.y };
			float proj = p.x * normal.x + p.y * normal.y;
			if (proj < minB) {
				minB = proj;
			}
			if (proj > maxB) {
				maxB = proj;
			}
		}

		// Check if the projections overlap
		if (maxA + buffer < minB || maxB < minA - buffer) {
			return false;
		}
	}
	return true;
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
	for (int i = 0; i < Collider::GetAllColliders().size(); i++)
	{
		Collider* colliderA = Collider::GetAllColliders()[i];
		for (int j = 0; j < Collider::GetAllColliders().size(); j++)
		{
			Collider* colliderB = Collider::GetAllColliders()[j];
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

void CollisionManager::VisualiseCollision()
{
	for (int i = 0; i < Collider::GetAllColliders().size(); i++)
	{
		Collider::GetAllColliders()[i]->Draw();
	}
}

