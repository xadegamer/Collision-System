 #include "CollisionManager.h"

#include <set>

const static int s_buffer = 1;

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
	else if (polyA != nullptr && polyB != nullptr)
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
	}
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
	// Get the world points of both polygons
	std::vector<Vector2> polyAPoints = A->GetWorldPoints();
	std::vector<Vector2> polyBPoints = B->GetWorldPoints();

	// Set up unique axes
	std::set<Vector2> uniqueAxes;

	// Get axes from polygon A
	for (int i = 0; i < A->GetNumPoints(); i++)
	{
		Vector2 edge = polyAPoints[(i + 1) % A->GetNumPoints()] - polyAPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Get axes from polygon B
	for (int i = 0; i < B->GetNumPoints(); i++)
	{
		Vector2 edge = polyBPoints[(i + 1) % B->GetNumPoints()] - polyBPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Check for overlap on each axis
	for (auto axis : uniqueAxes)
	{
		float polyAMin = INFINITY;
		float polyAMax = -INFINITY;
		float polyBMin = INFINITY;
		float polyBMax = -INFINITY;

		// Project polygon A onto axis
		for (auto point : polyAPoints)
		{
			float proj = Vector2::Dot(point, axis);
			polyAMin = std::min(polyAMin, proj);
			polyAMax = std::max(polyAMax, proj);
		}

		// Project polygon B onto axis
		for (auto point : polyBPoints)
		{
			float proj = Vector2::Dot(point, axis);
			polyBMin = std::min(polyBMin, proj);
			polyBMax = std::max(polyBMax, proj);
		}

		// Check for overlap
		float dist = std::max(polyBMin - polyAMax, polyAMin - polyBMax);
		if (dist > buffer)
		{
			return false;
		}
	}

	// If no separating axis found, the polygons overlap
	return true;
}

bool CollisionManager::PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer)
{
	// Get the world points of the polygon collider
	std::vector<Vector2> polyPoints = poly->GetWorldPoints();

	// Get the position of the circle collider in world space
	Vector2 circlePos = circle->GetPosition();

	// Create axes to test against (only need axes perpendicular to the edges of the polygon)
	std::vector<Vector2> axes;
	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		Vector2 edge = polyPoints[(i + 1) % poly->GetNumPoints()] - polyPoints[i];
		axes.push_back(Vector2(-edge.y, edge.x).Normalized());
	}

	// Add the axis perpendicular to the line segment connecting the circle center and the closest point on the polygon to the circle center
	float minDist = INFINITY;
	Vector2 closestPointOnPoly = Vector2::Zero();
	for (auto point : polyPoints)
	{
		Vector2 toCircle = circlePos - point;
		float dist = toCircle.Length();
		if (dist < minDist)
		{
			minDist = dist;
			closestPointOnPoly = point;
		}
	}
	axes.push_back((closestPointOnPoly - circlePos).Normalized());

	// Test for overlap on each axis
	for (auto axis : axes)
	{
		float polyMin = INFINITY;
		float polyMax = -INFINITY;
		float circleMin = INFINITY;
		float circleMax = -INFINITY;

		// Project the polygon onto the axis
		for (auto point : polyPoints)
		{
			float proj = Vector2::Dot(point, axis);
			polyMin = std::min(polyMin, proj);
			polyMax = std::max(polyMax, proj);
		}

		// Project the circle onto the axis
		float circleCentreProj = Vector2::Dot(circlePos, axis);
		circleMin = circleCentreProj - circle->GetRadius();
		circleMax = circleCentreProj + circle->GetRadius();

		// Test for overlap
		float dist = std::max(circleMin - polyMax, polyMin - circleMax);
		if (dist > buffer)
		{
			return false;
		}
	}

	// If no separating axis found, the polygon and circle overlap
	return true;
}

bool CollisionManager::PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer)
{
	// Get the world points of the polygon and box colliders
	std::vector<Vector2> polyPoints = poly->GetWorldPoints();
	std::vector<Vector2> boxPoints = box->GetWorldPoints();

	// Create axes to test against
	std::vector<Vector2> axes;
	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		Vector2 edge = polyPoints[(i + 1) % poly->GetNumPoints()] - polyPoints[i];
		axes.push_back(Vector2(-edge.y, edge.x).Normalized());
	}

	axes.push_back(Vector2(1, 0));
	axes.push_back(Vector2(0, 1));

	// Test for overlap on each axis
	for (auto axis : axes)
	{
		float polyMin = INFINITY;
		float polyMax = -INFINITY;
		float boxMin = INFINITY;
		float boxMax = -INFINITY;

		// Project the polygon onto the axis
		for (auto point : polyPoints)
		{
			float proj = Vector2::Dot(point, axis);
			polyMin = std::min(polyMin, proj);
			polyMax = std::max(polyMax, proj);
		}

		// Project the box onto the axis
		for (auto point : boxPoints)
		{
			float proj = Vector2::Dot(point, axis);
			boxMin = std::min(boxMin, proj);
			boxMax = std::max(boxMax, proj);
		}

		// Test for overlap
		float dist = std::max(boxMin - polyMax, polyMin - boxMax);
		if (dist > buffer)
		{
			return false;
		}
	}

	// If no separating axis found, the polygons overlap
	return true;
}

double CollisionManager::DistanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

bool CollisionManager::PolygonContainsPoint(const std::vector<Vector2>& polyPoints, const Vector2& point)
{
	bool contains = false;
	int i, j = polyPoints.size() - 1;
	for (i = 0; i < polyPoints.size(); i++)
	{
		if ((polyPoints[i].y < point.y && polyPoints[j].y >= point.y || polyPoints[j].y < point.y && polyPoints[i].y >= point.y) &&
			(polyPoints[i].x + (point.y - polyPoints[i].y) / (polyPoints[j].y - polyPoints[i].y) * (polyPoints[j].x - polyPoints[i].x) < point.x))
		{
			contains = !contains;
		}
		j = i;
	}
	return contains;
}