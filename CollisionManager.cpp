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

bool CollisionManager::PolygonToPolygonCollisionCheck(PolygonCollider* A, PolygonCollider* B, int buffer)
{
	return false;
}

bool CollisionManager::PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer)
{
	return false;
}

bool CollisionManager::PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer)
{
	// Get the world points of the polygon collider
	std::vector<Vector2> poly_points = poly->GetPoints();

	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		poly_points[i].x += poly->GetPosition().x;
		poly_points[i].y += poly->GetPosition().y;
	}

	// Get the half dimensions of the box collider
	Vector2 box_half_size(box->GetWidth() / 2.0f, box->GetHeight() / 2.0f);

	// Get the world position of the box collider
	Vector2 box_pos = box->GetPosition();

	// Get the axes to project the polygon and box onto
	std::vector<Vector2> axes;

	// Get the edge normals of the polygon
	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		Vector2 p1 = poly_points[i];
		Vector2 p2 = poly_points[(i + 1) % poly->GetNumPoints()];

		Vector2 edge_normal = Vector2::Normalize(Vector2::Perpendicular(p2 - p1));
		axes.push_back(edge_normal);
	}

	// Get the edge normals of the box
	axes.push_back(Vector2(1.0f, 0.0f));
	axes.push_back(Vector2(0.0f, 1.0f));

	// Project the polygon and box onto the axes and check for overlap
	for (int i = 0; i < axes.size(); i++)
	{
		Vector2 axis = axes[i];

		// Project the polygon onto the axis
		float min_poly = Vector2::Dot(poly_points[0], axis);
		float max_poly = min_poly;
		for (int j = 1; j < poly->GetNumPoints(); j++)
		{
			float projection = Vector2::Dot(poly_points[j], axis);
			if (projection < min_poly)
			{
				min_poly = projection;
			}
			if (projection > max_poly)
			{
				max_poly = projection;
			}
		}

		// Project the box onto the axis
		float min_box = Vector2::Dot(box_pos - box_half_size, axis);
		float max_box = Vector2::Dot(box_pos + box_half_size, axis);

		// Check for overlap
		float overlap = std::min(max_poly, max_box) - std::max(min_poly, min_box);
		if (overlap < 0)
		{
			return false;
		}
	}

	// If all axes have overlap, then the polygon and box intersect
	return true;
}

bool CollisionManager::CheckCollision(Collider* colA, Collider* colB)
{
	BoxCollider* boxA = dynamic_cast<BoxCollider*>(colA);
	BoxCollider* boxB = dynamic_cast<BoxCollider*>(colB);

	CircleCollider* circleA = dynamic_cast<CircleCollider*>(colA);
	CircleCollider* circleB = dynamic_cast<CircleCollider*>(colB);

	PolygonCollider* polyA = dynamic_cast<PolygonCollider*>(colA);
	PolygonCollider* polyB = dynamic_cast<PolygonCollider*>(colB);

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
	/*else if (polyA != nullptr && polyB != nullptr)
	{
		return PolygonToPolygonCollisionCheck(polyA, polyB, s_buffer);
	}
	else if (polyA != nullptr && circleB != nullptr)
	{
		return PolygonToCircleCollisionCheck(polyA, circleB, s_buffer);
	}
	else if (circleA != nullptr && polyB != nullptr)
	{
		return PolygonToCircleCollisionCheck(polyB, circleA, s_buffer);
	}*/
	else if (polyA != nullptr && boxB != nullptr)
	{
		return PolygonToBoxCollisionCheck(polyA, boxB, s_buffer);
	}
	else if (boxA != nullptr && polyB != nullptr)
	{
		return PolygonToBoxCollisionCheck(polyB, boxA, s_buffer);
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

