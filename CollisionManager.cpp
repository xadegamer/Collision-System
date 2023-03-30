 #include "CollisionManager.h"

const static int s_buffer = 1;

bool CollisionManager::BoxToBoxCollisionCheck(BoxCollider* boxA, BoxCollider* boxB, int buffer)
{
	if (boxA->GetPosition().x + boxA->GetWidth() - buffer > boxB->GetPosition().x && boxA->GetPosition().x + buffer < boxB->GetPosition().x + boxB->GetWidth() && boxA->GetPosition().y + boxA->GetHeight() - buffer > boxB->GetPosition().y && boxA->GetPosition().y + buffer < boxB->GetPosition().y + boxB->GetHeight())
	{
		return true;
	}
	return false;
}

bool CollisionManager::CircleToCircleCollsionCheck(CircleCollider* A, CircleCollider* B, int buffer)
{
	float totalRadiusSquared = A->GetRadius() + B->GetRadius();
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	Vector2 circleCentreA = Vector2(A->GetPosition().x + A->GetRadius(), A->GetPosition().y + A->GetRadius());

	Vector2 circleCentreB = Vector2(B->GetPosition().x + B->GetRadius(), B->GetPosition().y + B->GetRadius());
	// if the distance between the centers of the circles is less than the sum of their radii
	if (DistanceSquared(circleCentreA.x, circleCentreA.y, circleCentreB.x, circleCentreB.y) < totalRadiusSquared)
	{
		// the circles have collided
		return true;
	}

	// otherwise the circles have not collided
	return false;
}

bool CollisionManager::BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer)
{
	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (circle->GetPosition().x < box->GetPosition().x)
	{
		cX = box->GetPosition().x;
	}
	else if (circle->GetPosition().x > box->GetPosition().x + box->GetWidth())
	{
		cX = box->GetPosition().x + box->GetWidth();
	}
	else
	{
		cX = circle->GetPosition().x;
	}

	//Find closest y offset
	if (circle->GetPosition().y < box->GetPosition().y)
	{
		cY = box->GetPosition().y;
	}
	else if (circle->GetPosition().y > box->GetPosition().y + box->GetHeight())
	{
		cY = box->GetPosition().y + box->GetHeight();
	}
	else
	{
		cY = circle->GetPosition().y;
	}

	//If the closest point is inside the circle
	if (DistanceSquared(circle->GetPosition().x, circle->GetPosition().y, cX, cY) < circle->GetRadius() * circle->GetRadius())
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

	//// Calculate the axes to project the polygons onto
	//std::vector<Vector2> axes;
	//for (int i = 0; i < A->num_points; i++) {
	//	Vector2 point1 = Vector2(A->points[i].x + A->position.x, A->points[i].y + A->position.y);
	//	Vector2 point2 = Vector2(A->points[(i + 1) % A->num_points].x + A->position.x, A->points[(i + 1) % A->num_points].y + A->position.y);
	//	Vector2 edge = (point2 - point1).Normalize();
	//	axes.push_back(Vector2(-edge.y, edge.x));
	//}
	//for (int i = 0; i < B->num_points; i++) {
	//	Vector2 point1 = Vector2(B->points[i].x + B->position.x, B->points[i].y + B->position.y);
	//	Vector2 point2 = Vector2(B->points[(i + 1) % B->num_points].x + B->position.x, B->points[(i + 1) % B->num_points].y + B->position.y);
	//	Vector2 edge = (point2 - point1).Normalize();
	//	axes.push_back(Vector2(-edge.y, edge.x));
	//}

	//// Check for overlap on each axis
	//for (auto& axis : axes) {
	//	float Amin = INFINITY, Amax = -INFINITY;
	//	float Bmin = INFINITY, Bmax = -INFINITY;

	//	for (int i = 0; i < A->num_points; i++) {
	//		Vector2 point = Vector2(A->points[i].x + A->position.x, A->points[i].y + A->position.y);
	//		float projection = point.Dot(axis);
	//		Amin = std::min(Amin, projection);
	//		Amax = std::max(Amax, projection);
	//	}
	//	for (int i = 0; i < B->num_points; i++) {
	//		Vector2 point = Vector2(B->points[i].x + B->position.x, B->points[i].y + B->position.y);
	//		float projection = point.Dot(axis);
	//		Bmin = std::min(Bmin, projection);
	//		Bmax = std::max(Bmax, projection);
	//	}

	//	if (Amax < Bmin || Bmax < Amin) {
	//		// There is a gap on this axis, so the polygons do not overlap
	//		return false;
	//	}
	//}


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
		return BoxToBoxCollisionCheck(boxA, boxB, s_buffer);
	}
	else if (circleA != nullptr && circleB != nullptr)
	{
		return CircleToCircleCollsionCheck(circleA, circleB, s_buffer);
	}
	else if (boxA != nullptr && circleB != nullptr)
	{
		return BoxToCircleCollsionCheck(boxA, circleB, s_buffer);
	}
	else if (circleA != nullptr && boxB != nullptr)
	{
		return BoxToCircleCollsionCheck(boxB, circleA, s_buffer);
	}

	return false;
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

